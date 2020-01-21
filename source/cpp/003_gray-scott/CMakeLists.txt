#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

option(USE_TIMERS "Use profiling timers")
if(USE_TIMERS)
  message(STATUS "Enabling profiling timers")
  add_definitions(-DENABLE_TIMERS)
endif()

add_executable(a2e_003_gray-scott
  simulation/main.cpp
  simulation/gray-scott.cpp
  simulation/settings.cpp
  simulation/writer.cpp
)
target_link_libraries(a2e_003_gray-scott adios2::adios2 MPI::MPI_C)
install(TARGETS a2e_003_gray-scott 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(a2e_003_pdf_calc analysis/pdf_calc.cpp)
target_link_libraries(a2e_003_pdf_calc adios2::adios2 MPI::MPI_C)
install(TARGETS a2e_003_pdf_calc 
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}) 

install(FILES "adios2.xml" "visit-bp4.session" "visit-bp4.session.gui" 
                           "visit-sst.session" "visit-sst.session.gui"                  
                           "simulation/settings-files.json"
                           "simulation/settings-staging.json"
                           "plot/decomp.py" "plot/gsplot.py" "plot/pdfplot.py"
                           "cleanup.sh" "README.md"
        DESTINATION 
        ${CMAKE_INSTALL_PREFIX}/share/adios2-examples/003_gray-scott)
        