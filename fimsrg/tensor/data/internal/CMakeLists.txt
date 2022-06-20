add_library(
  fermimsrg_tensor_data_internal
  data_buffer.h data_buffer.cc
)
target_include_directories(
  fermimsrg_tensor_data_internal
  PUBLIC
  ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
  fermimsrg_tensor_data_internal
  PRIVATE
  fermimsrg::memory
)
