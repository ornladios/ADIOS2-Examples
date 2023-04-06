enable_language(HIP)

add_executable(adios2-write-read-hip write-read-hip.cpp)
target_link_libraries(adios2-write-read-hip ${common_deps} hip::device)
add_test_helper(adios2-write-read-hip)
install(TARGETS adios2-write-read-hip
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
