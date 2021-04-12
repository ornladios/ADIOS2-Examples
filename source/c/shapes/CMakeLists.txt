#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#
add_library(mpivars OBJECT mpivars.c)
target_link_libraries(mpivars ${common_deps})

add_library(decomp OBJECT decomp.c)
target_link_libraries(decomp ${common_deps})

add_executable(adios2-global-array-fixed-write-c
        global-array-fixed-write.c)

target_link_libraries(adios2-global-array-fixed-write-c mpivars decomp ${common_deps})

add_executable(adios2-global-array-fixed-read-c
        global-array-fixed-read.c)

target_link_libraries(adios2-global-array-fixed-read-c mpivars decomp ${common_deps})
#add_executable(adios2-global-array-fixed-read-c
#        decomp.c
#        mpivars.c
#        global-array-fixed-read.c)
#add_test_helper(adios2-global-array-fixed-write-c)
#install( TARGETS adios2-global-array-fixed-write-c
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#        )