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

target_link_libraries(vampost PUBLIC ${ITENSOR_DIR}/lib/libitensor)