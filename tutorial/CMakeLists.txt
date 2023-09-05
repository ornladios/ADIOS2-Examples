set(sources
  00_helloworld/helloworld_solution.cxx
  00_helloworld_basic/helloworld_solution.cxx
  01_variables/variables_solution.cxx
  02_operators/operators_solution.cxx
)

foreach(src IN_LIST sources)
  set(name tutorial_${src})
  add_executable(${name} ${sources})
  target_link_libraries(${name} PUBLIC ADIOS2::ADIOS2)
endforeach()
