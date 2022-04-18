add_library(
    fermimsrg_profiling_internal
    profiling_event_data.h
    profiling_data.h profiling_data.cc
    profiling_database.h profiling_database.cc
)
target_include_directories(
    fermimsrg_profiling_internal
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
    fermimsrg_profiling_internal
    PUBLIC
    absl::flat_hash_map
    PRIVATE
    fermimsrg::checks
)
