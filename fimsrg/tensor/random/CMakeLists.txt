add_library(
  fermimsrg_tensor_random
  tensor2d.h tensor2d.cc
)
add_library(fermimsrg::tensor_random ALIAS fermimsrg_tensor_random)
target_include_directories(
  fermimsrg_tensor_random
  PUBLIC
  ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
  fermimsrg_tensor_random
  PUBLIC
  fermimsrg_tensor
)
