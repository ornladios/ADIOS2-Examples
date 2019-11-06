add_executable(heatVisualization heatVisualization.cpp
  VizOutput.h
  VizSettings.cpp VizSettings.h
)
target_link_libraries(heatVisualization adios2::adios2 MPI::MPI_C)

option(ADIOS2_EXAMPLES_HEAT_USE_VTKM "Enable VTK-m based visualization" OFF)
if(ADIOS2_EXAMPLES_HEAT_USE_VTKM)
  find_package(VTKm REQUIRED)

  target_sources(heatVisualization PRIVATE VizOutputVtkm.cpp)
  target_link_libraries(heatVisualization vtkm vtkm_rendering)
else()
  target_sources(heatVisualization PRIVATE VizOutputPrint.cpp)
endif()
