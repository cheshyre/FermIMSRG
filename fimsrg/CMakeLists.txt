add_subdirectory(utility)
add_subdirectory(tensor)

add_library(
    fermimsrg_version
    version.h version.cc
)
add_library(fermimsrg::version ALIAS fermimsrg_version)
target_include_directories(
    fermimsrg_version
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
    fermimsrg_version
    PRIVATE
    fmt::fmt
)
