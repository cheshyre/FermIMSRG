add_subdirectory(internal)

add_library(
    fermimsrg_memory
    allocate.h allocate.cc
    alignment.h alignment.cc
)
add_library(fermimsrg::memory ALIAS fermimsrg_memory)
target_include_directories(
    fermimsrg_memory
    PUBLIC
    ${FIMSRG_ROOT_DIR}
)
target_link_libraries(
    fermimsrg_memory
    PRIVATE
    fermimsrg_memory_internal
    fermimsrg::profiling
)
