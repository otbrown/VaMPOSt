cmake_minimum_required(VERSION 3.17.1)

project(
  VaMPOSt VERSION 0.1.0
  DESCRIPTION "Variational Matrix Product Operator Stationary state search"
  LANGUAGES CXX
)

option(VaMPOSt_BUILD_TESTS "Build the tests" ON)

set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}")
endif()

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

#add_subdirectory(src)

if (VaMPOSt_BUILD_TESTS)
  # testing setup
  # Catch2 Test Framework
  find_package(Catch2 REQUIRED)
  enable_testing()
  include(CTest)
  include(Catch)
  include(ParseAndAddCatchTests)
  set(PARSE_CATCH_TESTS_NO_HIDDEN_TESTS ON)

  #add_subdirectory(tests)
endif()