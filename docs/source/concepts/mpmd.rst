.. _section-mpmd:

##############
Why MPMD mode?
##############

Location of examples: ``source/fortran/adios-module/mpivars.F90``

MPMD (Multiple Program Multiple Data) mode is when we compose one MPI World from multiple executables. Usually one can launch two executables separately by two MPI launch commands (mpirun, jsrun, aprun, etc.) and each application will have its own world and own ``MPI_COMM_WORLD`` communicator. Sharing the world is  beneficial if the two codes know about each other and can use MPI for communicating with each other. The cost of preparing your code for MPMD mode is simply to expect other codes be present and avoid using MPI_COMM_WORLD for in-application operations. 

ADIOS has specialized solutions to use MPI for the data movement in a stream but it requires MPMD mode. If the steps in a stream is "fixed", i.e. the list of variables, their definition and the writing/reading patterns are the same in every step, the SSC engine of ADIOS can use one-sided MPI functions to push the data to the consumer quickly. SSC still works if the content of the steps change but needs to spend considerable amount of time to figure out which process of the consumer gets which portion of the data every step.

You don't need to use MPMD mode at all to get faster communication. RDMA and TCP based solutions are available to communicate between two or more separate concurrent applications (SST and DataMan engines). However, the effort to prepare your code for MPMD mode is very small, and it may come handy some day on some system to use MPI for ADIOS I/O. 

Split communicator
******************

The only thing required for MPMD mode is that each application has its own communicator that only includes the processes of that application. *MPI_COMM_WORLD* includes all processes created in one launch command. Therefore, the application must first create its own "app" communicator and then completely avoid using MPI_COMM_WORLD in the application code. 

MPI has an operation for this: ``MPI_Comm_split``. Each application must pick a unique ID ("color") to distinguish themselves from other applications. Additionally, every process can pick its new rank in the "app" communicator but the simplest way is to keep the original order of ranks. 

.. code-block:: fortran

    integer:: app_comm, rank, nproc
    integer:: wrank, wnproc
    integer:: ierr
    integer, parameter:: color = 7215

    call MPI_Init(ierr)
    ! World comm spans all applications started with the same mpirun command 
    call MPI_Comm_rank(MPI_COMM_WORLD, wrank, ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, wnproc, ierr)

    ! Have to split and create a 'world' communicator for this app only
    ! color must be unique for each application 
    call MPI_Comm_split (MPI_COMM_WORLD, color, wrank, app_comm, ierr)
    call MPI_Comm_rank (app_comm, rank, ierr)
    call MPI_Comm_size (app_comm, nproc , ierr)


.. code-block:: c

    MPI_Init(&argc, &argv);

    int wrank, wnproc;
    MPI_Comm_rank(MPI_COMM_WORLD, &wrank);
    MPI_Comm_size(MPI_COMM_WORLD, &wnproc);

    const unsigned int color = 18325;
    MPI_Comm app_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, wrank, &app_comm);

    int rank, nproc;
    MPI_Comm_rank(app_comm, &rank);
    MPI_Comm_size(app_comm, &nproc);

.. code-block:: python

    from mpi4py import MPI

    color = 3231
    wrank = MPI.COMM_WORLD.Get_rank()
    wnproc = MPI.COMM_WORLD.Get_size()
    app_comm = MPI.COMM_WORLD.Split(color, wrank) 
    nproc = app_comm.Get_size()
    rank = app_comm.Get_rank()
