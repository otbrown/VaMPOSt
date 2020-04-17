add_executable(
  c2UnitTests c2UnitTests.cpp
)

target_compile_features(c2UnitTests PUBLIC cxx_std_17)

target_link_libraries(c2UnitTests 
  Catch2::Catch2 
  vampost
)
ParseAndAddCatchTests(c2UnitTests)