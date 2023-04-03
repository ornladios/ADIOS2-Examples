enable_language(CUDA)

add_executable(adios2-write-read-cuda write-read-cuda.cpp)
target_sources(adios2-write-read-cuda PRIVATE cudaRoutines.cu)
target_link_libraries(adios2-write-read-cuda ${common_deps} CUDA::cudart)
add_test_helper(adios2-write-read-cuda)
install(TARGETS adios2-write-read-cuda
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
