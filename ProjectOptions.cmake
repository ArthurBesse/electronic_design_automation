include(cmake/SystemLink.cmake)
include(cmake/LibFuzzer.cmake)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)


macro(electronic_design_automation_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

macro(electronic_design_automation_setup_options)
  option(electronic_design_automation_ENABLE_HARDENING "Enable hardening" ON)
  option(electronic_design_automation_ENABLE_COVERAGE "Enable coverage reporting" OFF)
  cmake_dependent_option(
    electronic_design_automation_ENABLE_GLOBAL_HARDENING
    "Attempt to push hardening options to built dependencies"
    ON
    electronic_design_automation_ENABLE_HARDENING
    OFF)

  electronic_design_automation_supports_sanitizers()

  if(NOT PROJECT_IS_TOP_LEVEL OR electronic_design_automation_PACKAGING_MAINTAINER_MODE)
    option(electronic_design_automation_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(electronic_design_automation_WARNINGS_AS_ERRORS "Treat Warnings As Errors" OFF)
    option(electronic_design_automation_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(electronic_design_automation_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(electronic_design_automation_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(electronic_design_automation_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(electronic_design_automation_ENABLE_PCH "Enable precompiled headers" OFF)
    option(electronic_design_automation_ENABLE_CACHE "Enable ccache" OFF)
  else()
    option(electronic_design_automation_ENABLE_IPO "Enable IPO/LTO" ON)
    option(electronic_design_automation_WARNINGS_AS_ERRORS "Treat Warnings As Errors" ON)
    option(electronic_design_automation_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${SUPPORTS_ASAN})
    option(electronic_design_automation_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${SUPPORTS_UBSAN})
    option(electronic_design_automation_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(electronic_design_automation_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(electronic_design_automation_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(electronic_design_automation_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(electronic_design_automation_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(electronic_design_automation_ENABLE_PCH "Enable precompiled headers" OFF)
    option(electronic_design_automation_ENABLE_CACHE "Enable ccache" ON)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      electronic_design_automation_ENABLE_IPO
      electronic_design_automation_WARNINGS_AS_ERRORS
      electronic_design_automation_ENABLE_USER_LINKER
      electronic_design_automation_ENABLE_SANITIZER_ADDRESS
      electronic_design_automation_ENABLE_SANITIZER_LEAK
      electronic_design_automation_ENABLE_SANITIZER_UNDEFINED
      electronic_design_automation_ENABLE_SANITIZER_THREAD
      electronic_design_automation_ENABLE_SANITIZER_MEMORY
      electronic_design_automation_ENABLE_UNITY_BUILD
      electronic_design_automation_ENABLE_CLANG_TIDY
      electronic_design_automation_ENABLE_CPPCHECK
      electronic_design_automation_ENABLE_COVERAGE
      electronic_design_automation_ENABLE_PCH
      electronic_design_automation_ENABLE_CACHE)
  endif()

  electronic_design_automation_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (electronic_design_automation_ENABLE_SANITIZER_ADDRESS OR electronic_design_automation_ENABLE_SANITIZER_THREAD OR electronic_design_automation_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(electronic_design_automation_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

macro(electronic_design_automation_global_options)
  if(electronic_design_automation_ENABLE_IPO)
    include(cmake/InterproceduralOptimization.cmake)
    electronic_design_automation_enable_ipo()
  endif()

  electronic_design_automation_supports_sanitizers()

  if(electronic_design_automation_ENABLE_HARDENING AND electronic_design_automation_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR electronic_design_automation_ENABLE_SANITIZER_UNDEFINED
       OR electronic_design_automation_ENABLE_SANITIZER_ADDRESS
       OR electronic_design_automation_ENABLE_SANITIZER_THREAD
       OR electronic_design_automation_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    message("${electronic_design_automation_ENABLE_HARDENING} ${ENABLE_UBSAN_MINIMAL_RUNTIME} ${electronic_design_automation_ENABLE_SANITIZER_UNDEFINED}")
    electronic_design_automation_enable_hardening(electronic_design_automation_options ON ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()
endmacro()

macro(electronic_design_automation_local_options)
  if(PROJECT_IS_TOP_LEVEL)
    include(cmake/StandardProjectSettings.cmake)
  endif()

  add_library(electronic_design_automation_warnings INTERFACE)
  add_library(electronic_design_automation_options INTERFACE)

  include(cmake/CompilerWarnings.cmake)
  electronic_design_automation_set_project_warnings(
    electronic_design_automation_warnings
    ${electronic_design_automation_WARNINGS_AS_ERRORS}
    ""
    ""
    ""
    "")

  if(electronic_design_automation_ENABLE_USER_LINKER)
    include(cmake/Linker.cmake)
    configure_linker(electronic_design_automation_options)
  endif()

  include(cmake/Sanitizers.cmake)
  electronic_design_automation_enable_sanitizers(
    electronic_design_automation_options
    ${electronic_design_automation_ENABLE_SANITIZER_ADDRESS}
    ${electronic_design_automation_ENABLE_SANITIZER_LEAK}
    ${electronic_design_automation_ENABLE_SANITIZER_UNDEFINED}
    ${electronic_design_automation_ENABLE_SANITIZER_THREAD}
    ${electronic_design_automation_ENABLE_SANITIZER_MEMORY})

  set_target_properties(electronic_design_automation_options PROPERTIES UNITY_BUILD ${electronic_design_automation_ENABLE_UNITY_BUILD})

  if(electronic_design_automation_ENABLE_PCH)
    target_precompile_headers(
      electronic_design_automation_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(electronic_design_automation_ENABLE_CACHE)
    include(cmake/Cache.cmake)
    electronic_design_automation_enable_cache()
  endif()

  include(cmake/StaticAnalyzers.cmake)
  if(electronic_design_automation_ENABLE_CLANG_TIDY)
    electronic_design_automation_enable_clang_tidy(electronic_design_automation_options ${electronic_design_automation_WARNINGS_AS_ERRORS})
  endif()

  if(electronic_design_automation_ENABLE_CPPCHECK)
    electronic_design_automation_enable_cppcheck(${electronic_design_automation_WARNINGS_AS_ERRORS} "" # override cppcheck options
    )
  endif()

  if(electronic_design_automation_ENABLE_COVERAGE)
    include(cmake/Tests.cmake)
    electronic_design_automation_enable_coverage(electronic_design_automation_options)
  endif()

  if(electronic_design_automation_WARNINGS_AS_ERRORS)
    check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
    if(LINKER_FATAL_WARNINGS)
      # This is not working consistently, so disabling for now
      # target_link_options(electronic_design_automation_options INTERFACE -Wl,--fatal-warnings)
    endif()
  endif()

  if(electronic_design_automation_ENABLE_HARDENING AND NOT electronic_design_automation_ENABLE_GLOBAL_HARDENING)
    include(cmake/Hardening.cmake)
    if(NOT SUPPORTS_UBSAN 
       OR electronic_design_automation_ENABLE_SANITIZER_UNDEFINED
       OR electronic_design_automation_ENABLE_SANITIZER_ADDRESS
       OR electronic_design_automation_ENABLE_SANITIZER_THREAD
       OR electronic_design_automation_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    electronic_design_automation_enable_hardening(electronic_design_automation_options OFF ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
