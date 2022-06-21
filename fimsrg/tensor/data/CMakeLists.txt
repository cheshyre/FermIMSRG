add_subdirectory(internal)

add_library(
  fermimsrg_tensor
  tensor2d.h tensor2d.cc
)
add_library(fermimsrg::tensor ALIAS fermimsrg_tensor)
target_include_directories(
  fermimsrg_tensor
  PUBLIC
  ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
  fermimsrg_tensor
  PUBLIC
  fermimsrg_tensor_data_internal
  PRIVATE
  fermimsrg::checks
  fermimsrg::memory
  fermimsrg::profiling
)
