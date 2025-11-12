
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0 # Always use a specific tag or hash
)
FetchContent_MakeAvailable(googletest)

# Enable testing for the project
enable_testing()

# Create an executable for your tests
add_executable(
    ${THE_TST}
    simpletron.t.cpp
)

# Link your test executable to the GTest libraries
# GTest::gtest_main includes the main() function for running all tests.
target_link_libraries(
    ${THE_TST}
    PRIVATE
    GTest::gtest_main
    ${THE_LIB}
)

# Automatically discover and register tests with CTest
include(GoogleTest) # Loads the gtest_discover_tests function
gtest_discover_tests(${THE_TST})