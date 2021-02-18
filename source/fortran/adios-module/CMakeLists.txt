add_executable(adios2-module-example main.F90 mpivars.F90 adiosio.F90)
target_compile_definitions(adios2-module-example PRIVATE ADIOS2)
target_link_libraries(adios2-module-example
  adios2::fortran_mpi MPI::MPI_Fortran
)
