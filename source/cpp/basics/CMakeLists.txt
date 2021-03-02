#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(adios2-variables-shapes-cpp variables-shapes.cpp)
target_link_libraries(adios2-variables-shapes-cpp ${common_deps})
add_test_helper(adios2-variables-shapes-cpp)
install(TARGETS adios2-variables-shapes-cpp 
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_executable(adios2-variables-shapes-hl-cpp variables-shapes-hl.cpp)
target_link_libraries(adios2-variables-shapes-hl-cpp ${common_deps})
add_test_helper(adios2-variables-shapes-hl-cpp) 
install(TARGETS adios2-variables-shapes-hl-cpp 
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(Threads_FOUND)
  add_executable(adios2-thread-write-cpp thread-write.cpp)
  target_link_libraries(adios2-thread-write-cpp ${common_deps} Threads::Threads)
  add_test_helper(adios2-thread-write-cpp)
  install(TARGETS adios2-thread-write-cpp 
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
endif()
