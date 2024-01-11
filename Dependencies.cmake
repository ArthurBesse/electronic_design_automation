include(cmake/CPM.cmake)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(electronic_design_automation_setup_dependencies)

  # For each dependency, see if it's
  # already been provided to us by a parent project

  if(NOT TARGET GTest::GTest)
    CPMAddPackage(
	  NAME googletest
	  GITHUB_REPOSITORY google/googletest
	  GIT_TAG v1.14.0
	  VERSION 1.14.0
	  OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt"
	)
  endif()
  # if(NOT TARGET tools::tools)
    # cpmaddpackage("gh:lefticus/tools#update_build_system")
  # endif()

endfunction()
