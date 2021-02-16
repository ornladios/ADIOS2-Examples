program adios2_global_arrays_changing_shape_write
    use mpivars
    use adios2
    implicit none
    integer, parameter :: numsteps = 5

    ! ADIOS2 variables
    type(adios2_adios) :: adios

    ! MPI then ADIOS2 initialization
    call init_mpi(123)
    call adios2_init(adios, app_comm, ierr)

    call writer()

    ! ADIOS2 then MPI finalization
    call adios2_finalize(adios, ierr)
    call finalize_mpi()

contains

subroutine writer
    use mpivars
    use decomp
    use adios2
    implicit none

    type(adios2_io) :: io
    type(adios2_engine) :: engine
    type(adios2_variable) :: var_g
    type(adios2_attribute) :: attr
    integer :: step

    ! Application variables
    ! g = 1D distributed array, both the global size and 
    !      the per-process size are changing every step

    integer, dimension(:), allocatable :: g
    character(80), parameter :: ga = "Global Array with changing shape and decomposition"

    integer, parameter :: mincount = 2, maxcount = 5
    integer*8, dimension(1) :: changing_shape, changing_start, changing_count

    call adios2_declare_io (io, adios, 'output', ierr)


    changing_count = 1 ! fake data is okay for now
    changing_shape = 1 ! we will change the shape,start,count in every step
    changing_start = 0
    call adios2_define_variable(var_g, io, "GlobalArray", &
                                adios2_type_integer4, 1, &
                                changing_count, changing_start, changing_count, &
                                adios2_variable_dims, ierr)

                                
    call adios2_define_attribute(attr, io, "GlobalArray/info", ga, ierr)
    
    call adios2_open(engine, io, "adios2-global-array-changing-shape-f.bp", adios2_mode_write, ierr)

    ! Computation/output loop
    do step=0,numsteps-1
        ! "compute g" where size of g will change
        changing_count = get_random(mincount, maxcount)
        call gather_decomp_1d(changing_count(1), changing_shape(1), changing_start(1))
        allocate(g(changing_count(1)))
        g = rank

        ! Change the shape and decomposition information for g2
        call adios2_set_shape(var_g, 1, changing_shape, ierr)
        call adios2_set_selection(var_g, 1, changing_start, changing_count, ierr);
        write (*,100) "Decomp rank=", rank, &
        " global shape = ", changing_shape(1),  &
        " local count = ", changing_count(1),  &
        " offset = ", changing_start(1) 
100 format (a,i2,a,i4,a,i4,a,i4)

        ! Output all data
        call adios2_begin_step(engine, adios2_step_mode_append, ierr)
        call adios2_put(engine, var_g, g, ierr);
        call adios2_end_step(engine, ierr)

        deallocate(g)
    enddo

    ! Close the output
    call adios2_close(engine, ierr)

    if (rank == 0) then
        write (*,*) "Try the following: "
        write (*,*) &
            " bpls -la adios2-global-array-changing-shape-f.bp"
        write (*,*) &
            " bpls -l adios2-global-array-changing-shape-f.bp -t"
        write (*,*) &
            " bpls -l adios2-global-array-changing-shape-f.bp/ GlobalArray -dt -n 9999"
        write (*,'(a)') &
            "  mpirun -n 2 ./adios2-global-array-changing-shape-read-f "
    endif

end subroutine writer


end program adios2_global_arrays_changing_shape_write
