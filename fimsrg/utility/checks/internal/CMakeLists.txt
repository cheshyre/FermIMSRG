add_library(
    fermimsrg_checks_internal
    assert_eval.h assert_eval.cc
)
target_include_directories(
    fermimsrg_checks_internal
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
