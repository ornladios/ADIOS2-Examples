program adios2_shapes
    use adios2
    implicit none
    include 'mpif.h'

    ! MPI variables
    integer:: app_comm, rank, nproc
    integer:: ierr  

    ! Application variables
    integer, parameter :: numsteps = 5
    integer :: step
    ! gv = Global Value (a single value from the entire application, changes over time)
    ! lv = Local Value (one value per process, changes over time)
    ! ga = 1D distributed array, every process fits into a global "shape"
    ! la = 2D array on each process that somehow does not fit a global 2D or 3D shape
    integer :: gv, lv
    real*8, dimension(5) :: ga
    real*4, dimension(:,:), allocatable :: la
    integer*8 :: lsize1, lsize2 ! the size of the local 2D var 'la'

    ! ADIOS variables
    type(adios2_adios) :: adios
    type(adios2_io) :: io
    type(adios2_engine) :: engine
    type(adios2_variable) :: var_gv, var_lv, var_ga, var_la

    ! MPI then ADIOS2 initialization
    call init_mpi()
    call adios2_init(adios, "shapes.xml", app_comm, ierr)

    ! Initialize and open output
    call adios2_declare_io (io, adios, 'Shapes', ierr)
    call adios2_open(engine, io, "adios2-shapes-f.bp", adios2_mode_write, ierr)

    ! Define the content of the output
    call define_global_value()
    call define_local_value()
    call define_global_array()
    call define_local_array()

    ! Computation/output loop
    do step=0,numsteps-1
        call compute(step)

        call adios2_begin_step(engine, adios2_step_mode_append, ierr)
        if (rank == 0) then
            ! could be written from every process but it is useless
            call adios2_put(engine, var_gv, gv, ierr);
        endif
        call adios2_put(engine, var_lv, lv, ierr);
        call adios2_put(engine, var_ga, ga, ierr);
        call adios2_put(engine, var_la, la, ierr);
        call adios2_end_step(engine, ierr)
    enddo

    ! Close the output
    call adios2_close(engine, ierr)

    ! ADIOS2 then MPI finalization
    call adios2_finalize(adios, ierr)
    call finalize_mpi()

contains

subroutine define_global_value
    implicit none
    call adios2_define_variable(var_gv, io, "GlobalValue", adios2_type_integer4, ierr)
end subroutine define_global_value

subroutine define_local_value
    implicit none
    ! Local values will show up in reading as a 1D array of nproc elements
    ! the write side definition is quite cumbersome in Fortran :-(
    ! We have to define it almost like a distributed global array with a special
    ! dimension value to indicate its type
    call adios2_define_variable(var_lv, io, "LocalValue", adios2_type_integer4, &
                                1, (/ adios2_local_value_dim /), &
                                adios2_null_dims, &
                                adios2_null_dims, &
                                adios2_constant_dims, ierr)
end subroutine define_local_value

subroutine define_global_array
    implicit none
    ! Distributed n-dimensional arrays have these properties
    ! number of dimensions
    ! the global shape: a virtual n-dimensional boundary
    ! a local size: the n-dimensional size of the array on each process
    ! an offset: the position of the local array in the global space
    integer(kind=8), dimension(1) :: shape_dims, start_dims, count_dims
    ! Note that these must be 64-bit integers 
    ! Lets put the 1D arrays into the simplest order, by rank, into a
    ! a "contiguous" 1D space
    count_dims(1) = 5_8
    shape_dims(1) = nproc * count_dims(1)
    start_dims(1) = rank * count_dims(1)

    call adios2_define_variable(var_ga, io, "GlobalArray", &
                                adios2_type_real8, 1, &
                                shape_dims, start_dims, count_dims, &
                                adios2_constant_dims, ierr)
    write (*,100) "Global Array rank=", rank, &
                  " local size = ", count_dims(1),  &
                  " offset = ", start_dims(1)
100 format (a,i2,a,i2,a,i2,a)

end subroutine define_global_array

subroutine define_local_array
    implicit none
    ! If the arrays per process don't fit a global shape in any way
    ! one can still write them under one name. However, at read, once
    ! has to retrieve them one-by-one, so use it only if there is no
    ! way to organize it otherwise.
    integer(kind=8), dimension(2) :: shape_dims, start_dims, count_dims
    lsize1 = mod(rank,6) + 1
    lsize2 = nproc - rank + 1
    count_dims(1) = lsize1
    count_dims(2) = lsize2
    call adios2_define_variable(var_la, io, "LocalArray", &
                                adios2_type_real4, 2, &
                                adios2_null_dims, adios2_null_dims, count_dims, &
                                adios2_constant_dims, ierr)
    write (*,'("Local Array rank=",i2," size={",2i5,"}")') rank, lsize1, lsize2
    allocate(la(lsize1,lsize2))
end subroutine define_local_array


subroutine compute(step)
    implicit none
    integer, intent(in):: step
    integer :: i, j
    gv = step
    lv = nproc*(step)+rank
    do i = 1,5
        ga(i) = step + rank/10.0 + i/100.0
    enddo
    do j = 1,lsize2
        do i = 1,lsize1
            la(i,j) = step + rank/10.0 + j/100.0 + i/1000.0
        enddo
    enddo
end subroutine compute


subroutine init_mpi
    implicit none
    integer, parameter:: color = 72152
    integer:: wrank, wnproc, ierr
    call MPI_Init(ierr)
    ! World comm spans all applications started with the same mpirun command 
    call MPI_Comm_rank(MPI_COMM_WORLD, wrank, ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, wnproc, ierr)

    ! Have to split and create a 'world' communicator for this app only
    ! color must be unique for each application 
    call MPI_Comm_split (MPI_COMM_WORLD, color, wrank, app_comm, ierr)
    call MPI_Comm_rank (app_comm, rank, ierr)
    call MPI_Comm_size (app_comm, nproc , ierr)
end subroutine init_mpi

subroutine finalize_mpi()
    integer:: ierr
    call MPI_Finalize(ierr)
end subroutine finalize_mpi

end program adios2_shapes