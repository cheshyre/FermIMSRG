add_subdirectory(internal)

add_library(
    fermimsrg_profiling
    profile_report.h profile_report.cc
    function_profile.h
)
add_library(fermimsrg::profiling ALIAS fermimsrg_profiling)
target_include_directories(
    fermimsrg_profiling
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
    fermimsrg_profiling
    PUBLIC
    fermimsrg_profiling_internal
)
