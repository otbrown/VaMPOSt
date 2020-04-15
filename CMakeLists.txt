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

# add blas and lapack using FindBLAS, have to deal with
# include directories separately, requires either MKLROOT
# or BLAS_ROOT to be defined as an input to cmake
if(DEFINED MKLROOT)
  message("MKLROOT=${MKLROOT}. Adding to environment.")
  set(ENV{MKLROOT} ${MKLROOT})
  set(BLAS_INCLUDE_DIR ${MKLROOT}/include)
endif()

if(DEFINED BLAS_ROOT)
  message("BLAS_ROOT=${BLAS_ROOT}.")
  set(BLAS_INCLUDE_DIR ${BLAS_ROOT}/include)
endif()

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

# add ITENSOR_DIR -- if it's not been defined as an 
# input cmake variable we assume ITensor has been 
# included in the submodule
if (NOT DEFINED ITENSOR_DIR)
  set(ITENSOR_DIR "${CMAKE_SOURCE_DIR}/external/ITensor" CACHE PATH 
    "Location of the ITensor root directory.")
else()
  set(ITENSOR_DIR "${ITENSOR_DIR}" CACHE PATH 
    "Location of the ITensor root directory")
endif()
message("ITENSOR_DIR=${ITENSOR_DIR}")

add_subdirectory(src)

if (VaMPOSt_BUILD_TESTS)
  # testing setup
  # Catch2 Test Framework
  find_package(Catch2 REQUIRED)
  enable_testing()
  include(CTest)
  include(Catch)
  include(ParseAndAddCatchTests)
  set(PARSE_CATCH_TESTS_NO_HIDDEN_TESTS ON)
endif()