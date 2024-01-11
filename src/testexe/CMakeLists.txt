add_executable(testexe main.cpp)

target_link_libraries(
  testexe
  PRIVATE electronic_design_automation::electronic_design_automation_options
          electronic_design_automation::electronic_design_automation_warnings
          electronic_design_automation::libcircuit)



target_include_directories(testexe PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
