# ------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
# ------------------------------------------------------------------------------#

add_executable(adios2-gray-scott-struct
        simulation/main.cpp
        simulation/gray-scott.cpp
        simulation/settings.cpp
        simulation/writer.cpp
        simulation/restart.cpp
)
target_link_libraries(adios2-gray-scott-struct adios2::adios2 MPI::MPI_C)
install(TARGETS adios2-gray-scott-struct
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

add_executable(adios2-pdf-calc-struct analysis/pdf-calc.cpp)
target_link_libraries(adios2-pdf-calc-struct adios2::adios2 MPI::MPI_C)
install(TARGETS adios2-pdf-calc-struct
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(FILES "adios2.xml" "adios2-inline-plugin.xml"
        "visit-bp4.session" "visit-bp4.session.gui"
        "visit-sst.session" "visit-sst.session.gui"
        "simulation/settings-files.json"
        "simulation/settings-staging.json"
        "simulation/settings-inline.json"
        "plot/decomp.py" "plot/gsplot.py" "plot/pdfplot.py"
        "README.md"
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/adios2-examples/gray-scott-struct)

install(DIRECTORY "catalyst"
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/adios2-examples/gray-scott-struct)

install(PROGRAMS "cleanup.sh"
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/adios2-examples/gray-scott-struct)
