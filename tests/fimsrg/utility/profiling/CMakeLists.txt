add_executable(
    function_profile_test
    function_profile_test.cc
)
target_link_libraries(
    function_profile_test
    fermimsrg::profiling
    Catch2::Catch2WithMain
)
catch_discover_tests(
    function_profile_test
)
