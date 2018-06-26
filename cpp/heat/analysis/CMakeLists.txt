add_executable(heatAnalysis heatAnalysis.cpp
  AnalysisSettings.cpp AnalysisSettings.h
)
target_link_libraries(heatAnalysis adios2::adios2 MPI::MPI_C)
