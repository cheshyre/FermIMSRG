add_library(
    fermimsrg_profiling_internal
    profiling_event_data.h
    profiling_data.h profiling_data.cc
)
target_include_directories(
    fermimsrg_profiling_internal
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
    fermimsrg_profiling_internal
    PRIVATE
    fermimsrg::checks
)
