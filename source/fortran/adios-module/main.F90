program adios2_module_example
    use mpivars
#ifdef ADIOS2
    use adiosio
#endif
    implicit none

    integer, parameter :: numsteps = 5
    integer :: step
    type(adios2_io) :: iotest
    type(adios2_variable) :: vartest

    call init_mpi(12345)
#ifdef ADIOS2
    call init_adiosio()
#endif

    call adios2_declare_io (iotest, adios2obj, 'Test', ierr)
    if (.not.iotest%valid) then
        write(*,*) "Error when creating test IO object"
    endif   


    call diag_init()
    do step=1,numsteps,1
        call diag_writer(step)
    enddo
    call diag_finalize()

    call reader()

#ifdef ADIOS2
    call finalize_adiosio()
#endif
    call finalize_mpi()

contains

subroutine diag_init
    use adiosio
    implicit none
    type(adios2_variable) :: var
    ! var reference will disappear on return but the variable definition is 
    ! accessible by using the name of the variable ("step")
    call adios2_declare_io (io_diag, adios2obj, 'DiagnosticsOutput', ierr)
    call adios2_open(engine_diag, io_diag, "diag.bp", adios2_mode_write, ierr)
    call adios2_define_variable(var, io_diag, "step", adios2_type_integer4, ierr)
end subroutine diag_init


subroutine diag_writer(step)
    use adiosio
    implicit none
    integer, intent(in):: step
    call adios2_begin_step(engine_diag, adios2_step_mode_append, ierr)
    call adios2_put(engine_diag, "step", step, ierr)
    call adios2_end_step(engine_diag, ierr)
end subroutine diag_writer


subroutine diag_finalize
    use adiosio
    implicit none
    call adios2_close(engine_diag, ierr)
end subroutine diag_finalize


subroutine reader
    use adiosio
    use mpivars
    implicit none

    type(adios2_variable) :: var
    type(adios2_io) :: io
    type(adios2_engine) :: engine
    integer*8 :: numsteps
    integer*4, dimension(:), allocatable :: steps
    integer :: i
    character(len=80)::fmt

    if (rank == 0) then
        call adios2_declare_io(io, adios2obj, "DiagnosticsInput", ierr)
        call adios2_open(engine, io, "diag.bp", adios2_mode_read, MPI_COMM_SELF, ierr)
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

end program adios2_module_example
