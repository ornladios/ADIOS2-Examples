add_executable(heatSimulation
  heatSimulation.cpp
  HeatTransfer.cpp HeatTransfer.h
  IO_adios2.cpp IO.h
  Settings.cpp Settings.h
)
target_link_libraries(heatSimulation adios2::adios2 MPI::MPI_C)
