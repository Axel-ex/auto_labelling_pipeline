cmake_minimum_required(VERSION 3.8)

set(This first_opencv_test)

set(Sources
    test.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")

# Create the test executable
add_executable(${This} ${Sources})

# Link the test executable with the Example library and gtest_main
target_link_libraries(${This}
	PUBLIC
    first_opencv_lib  # Link with the Example library
    gtest_main  # Link with gtest_main
)

# Add the test with a non-empty name
add_test(
    NAME ${This}_test  # Provide a non-empty name for the test
    COMMAND ${This}  # Specify the test executable to run
)
