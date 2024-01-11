cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(electronic_design_automation CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET electronic_design_automation_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

find_package(GoogleTest)
# # Provide a simple smoke test to make sure that the CLI works and can display a --help message
# add_test(NAME cli.has_help COMMAND intro --help)

# # Provide a test to verify that the version being reported from the application
# # matches the version given to CMake. This will be important once you package
# # your program. Real world shows that this is the kind of simple mistake that is easy
# # to make, but also easy to test for.
# add_test(NAME cli.version_matches COMMAND intro --version)
# set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")

add_executable(tests Graph.cpp)

target_link_libraries(
  tests
  GTest::gtest_main
  electronic_design_automation::libcircuit
)

target_include_directories(tests PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

include(GoogleTest)
gtest_discover_tests(tests)

if(WIN32 AND BUILD_SHARED_LIBS)
  add_custom_command(
    TARGET tests
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:tests> $<TARGET_FILE_DIR:tests>
    COMMAND_EXPAND_LISTS)
endif()


