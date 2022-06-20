add_library(
  fermimsrg_tensor_data_internal
  data_buffer.h data_buffer.cc
)
target_include_directories(
  fermimsrg_tensor_data_internal
  PUBLIC
  ${FIMSRG_ROOT_DIR}
)
