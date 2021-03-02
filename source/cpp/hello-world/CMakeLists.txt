
add_executable(adios2-hello-world-cpp hello-world.cpp)
target_link_libraries(adios2-hello-world-cpp ${common_deps})
add_test_helper(adios2-hello-world-cpp)
install(TARGETS adios2-hello-world-cpp
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_executable(adios2-hello-world-hl-cpp hello-world-hl.cpp)
target_link_libraries(adios2-hello-world-hl-cpp ${common_deps})
add_test_helper(adios2-hello-world-hl-cpp)
install(TARGETS adios2-hello-world-hl-cpp
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
