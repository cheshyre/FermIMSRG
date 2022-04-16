cmake_minimum_required(VERSION 3.10)

project(FermIMSRG VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FIMSRG_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_compile_options(
    "-Wall"
    "-Wextra"
    "-Werror"
    "$<$<CONFIG:RELEASE>:-O3>"
)

# Add external lib directory
add_subdirectory(lib)

# Add src directory
add_subdirectory(fimsrg)

# Enable ctest
include(CTest)
enable_testing()

# and Catch2 helper
include(lib/Catch2/contrib/Catch.cmake)

# Unit tests
add_subdirectory(tests)
