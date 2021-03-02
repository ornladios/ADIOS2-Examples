add_library(_mpivars OBJECT mpivars.F90)
target_link_libraries(_mpivars MPI::MPI_Fortran)

add_library(_decomp OBJECT decomp.F90)
target_link_libraries(_decomp _mpivars)

add_executable(adios2-values-f values.F90)
target_link_libraries(adios2-values-f adios2::fortran_mpi _mpivars)

add_executable(adios2-global-array-fixed-write-f global-array-fixed-write.F90)
target_link_libraries(adios2-global-array-fixed-write-f
  adios2::fortran_mpi _mpivars _decomp
)

add_executable(adios2-global-array-fixed-read-f global-array-fixed-read.F90)
target_link_libraries(adios2-global-array-fixed-read-f
  adios2::fortran_mpi _mpivars _decomp
)

add_executable(adios2-global-array-changing-shape-write-f
  global-array-changing-shape-write.F90
)
target_link_libraries(adios2-global-array-changing-shape-write-f
  adios2::fortran_mpi _mpivars _decomp
)

#add_executable(adios2-shapes-write-f shapes-write.F90)
#target_link_libraries(adios2-shapes-write-f
#  adios2::fortran_mpi MPI::MPI_Fortran
#)

#add_executable(adios2-shapes-read-f shapes-read.F90)
#target_link_libraries(adios2-shapes-read-f
#  adios2::fortran_mpi MPI::MPI_Fortran
#)
