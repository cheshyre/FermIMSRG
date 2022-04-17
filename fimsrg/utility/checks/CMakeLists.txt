add_subdirectory(internal)

add_library(
    fermimsrg_checks
    assert.h assert.cc
)
add_library(fermimsrg::checks ALIAS fermimsrg_checks)
target_include_directories(
    fermimsrg_checks
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
    fermimsrg_checks
    PUBLIC
    fermimsrg_checks_internal
)
