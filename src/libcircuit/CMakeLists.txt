include(GenerateExportHeader)


add_library(libcircuit libcircuit.cpp)



add_library(electronic_design_automation::libcircuit ALIAS libcircuit)

target_link_libraries(libcircuit PRIVATE electronic_design_automation_options electronic_design_automation_warnings)

target_include_directories(libcircuit ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(libcircuit PUBLIC cxx_std_20)

set_target_properties(
  libcircuit
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(libcircuit EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/electronic_design_automation/libcircuit_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(libcircuit PUBLIC libcircuit_STATIC_DEFINE)
endif()
