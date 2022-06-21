add_subdirectory(internal)

add_executable(
  tensor2d_test
  tensor2d_test.cc
)
target_link_libraries(
  tensor2d_test
  fermimsrg::tensor
  fermimsrg::memory
  Catch2::Catch2WithMain
)
catch_discover_tests(
  tensor2d_test
)
