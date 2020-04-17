add_library(libitensor STATIC IMPORTED)

target_include_directories(libitensor
  INTERFACE
  ${ITENSOR_DIR}/itensor
  ${BLAS_INCLUDE_DIR}
)

set_target_properties(libitensor 
  PROPERTIES 
  IMPORTED_LOCATION ${ITENSOR_DIR}/lib/libitensor.a
)

add_library(vampost
  STATIC
  dmpo.cpp
)

target_compile_features(vampost PUBLIC cxx_std_17)

target_include_directories(vampost
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/include
  ${ITENSOR_DIR}
  ${BLAS_INCLUDE_DIR}
)

target_link_libraries(vampost 
  PUBLIC 
  libitensor 
  ${BLAS_LIBRARIES} 
  ${LAPACK_LIBRARIES}
)