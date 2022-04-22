add_library(
    fermimsrg_memory_internal
    alignment.h
    basic_allocator.h
    pooled_allocator.h pooled_allocator.cc
)
target_include_directories(
    fermimsrg_memory_internal
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
    fermimsrg_memory_internal
    PUBLIC
    absl::flat_hash_map
    PRIVATE
    fermimsrg::checks
)
