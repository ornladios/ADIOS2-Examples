#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(adios2-hello-world-c hello-world.c)
target_link_libraries(adios2-hello-world-c ${common_deps})
add_test_helper(adios2-hello-world-c)
install(TARGETS adios2-hello-world-c
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
