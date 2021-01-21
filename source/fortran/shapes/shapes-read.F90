program adios2_shapes
    use adios2
    implicit none
    include 'mpif.h'

    ! MPI variables
    integer:: app_comm, rank, nproc
    integer:: ierr  

    ! Application variables
    integer :: numsteps
    integer :: step
    ! gv = Global Value (a single value from the entire application, changes over time)
    ! lv = Local Value (one value per process, changes over time)
    ! ga = 1D distributed array, every process fits into a global "shape"
    ! la = 2D array on each process that somehow does not fit a global 2D or 3D shape
    integer :: gv, lv
    integer, dimension(:), allocatable :: ga
    integer, dimension(:,:), allocatable :: la

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
    call adios2_open(engine, io, "adios2-shapes-f.bp", adios2_mode_read, ierr)

 

    ! Computation/output loop
    do step=1,numsteps,1
        call adios2_begin_step(engine, adios2_step_mode_append, ierr)
        call write_global_value(step)
        call write_local_value(step)
        call write_global_array(step)
        call write_local_array(step)
        if (step == 1) then
            call adios2_put(engine, var_gc, nproc, ierr);
            call adios2_put(engine, var_lc, rank, ierr);
        endif
        if (rank == 0) then
            call adios2_put(engine, var_gv, gv, ierr);
        endif
        call adios2_put(engine, var_lv, lv, ierr);
        call adios2_end_step(engine, ierr)
    enddo

    ! Close the output
    call close_output()

    ! Now read back all
    call reader()

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
    call adios2_define_variable(var_gv, io, "GlobalValue", adios2_type_integer4, ierr)
end subroutine define_global_value

subroutine compute(step)
    implicit none
    integer, intent(in):: step
    gv = step
    lv = nproc*(step-1)+rank
    
end subroutine write_global_value

subroutine reader
    implicit none

    type(adios2_variable) :: var
    type(adios2_io) :: io
    type(adios2_engine) :: engine
    integer*8 :: numsteps
    integer*4, dimension(:), allocatable :: steps
    integer :: i
    character(len=80)::fmt

    if (rank == 0) then
        call adios2_declare_io(io, adios, "ShapesRead", ierr)
        call adios2_open(engine, io, "adios2-shapes-f.bp", adios2_mode_read, MPI_COMM_SELF, ierr)
        call adios2_inquire_variable(var, io, "step", ierr)
        call adios2_variable_steps(numsteps, var, ierr)
        call adios2_set_step_selection(var, 0_8, numsteps, ierr)
        allocate(steps(numsteps))
        call adios2_get(engine, var, steps , ierr)
        call adios2_close(engine, ierr)
        write(*,'(a,i5)') "Number of steps in diag.bp = ", numsteps
        write(fmt,'(a,i5,a)') '(a10,',numsteps,'i4,a2)'
        !write(*,'(a)') fmt
        write(*,fmt) "Steps = [", steps, " ]"
        deallocate(steps)
    endif
end subroutine reader

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