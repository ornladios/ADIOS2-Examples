program example_mpi
    use mpi
    use adios2

    implicit none

    character(*), parameter :: greeting = &
                  "Hello World from ADIOS2 Fortran/MPI example"
    integer(kind=8), dimension(1) :: shape_dims, start_dims, count_dims
    integer :: irank, isize, ierr, var_type
    type(adios2_adios) :: adios
    type(adios2_io) :: io
    type(adios2_engine) :: engine

    call MPI_Init(ierr)
    call MPI_Comm_rank(MPI_COMM_WORLD, irank, ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, isize, ierr)
#if (defined(ADIOS2_VERSION) && (ADIOS2_VERSION >= 20900)) || defined(ADIOS2_DEBUGMODE_REMOVED)
    call adios2_init(adios, MPI_COMM_WORLD, ierr)
#else
    call adios2_init(adios, MPI_COMM_WORLD, adios2_debug_mode_on, ierr)
#endif

    call writer()
    call reader()

    call adios2_finalize(adios, ierr)

    call MPI_Finalize(ierr)

contains

subroutine writer
    type(adios2_variable) :: var
    call adios2_declare_io(io, adios, "hello-world-writer", ierr)
    call adios2_define_variable(var, io, "Greeting", adios2_type_string, ierr)
    call adios2_open(engine, io, "example-mpi-f.bp", adios2_mode_write, ierr)
    call adios2_put(engine, var, greeting, ierr)
    call adios2_close(engine, ierr)
end subroutine writer


subroutine reader
    character(len=40) :: msg
    integer*4 :: ndims
    integer*8, dimension(:), allocatable :: dims
    type(adios2_variable) :: var

    call adios2_declare_io(io, adios, "hello-world-reader", ierr)
    call adios2_open(engine, io, "example-mpi-f.bp", adios2_mode_read, ierr)
    call adios2_inquire_variable(var, io, "Greeting", ierr)
    call adios2_get(engine, var, msg, ierr)
    call adios2_close(engine, ierr)
    write(*,*) trim(msg)
end subroutine reader

end program example_mpi
