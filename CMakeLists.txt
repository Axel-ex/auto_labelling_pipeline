cmake_minimum_required(VERSION 3.14)

# Project information
project(auto_labelling_pipeline C CXX)

set(exec_name labelling_pipeline)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Paths for source and headers
set(src_dir sources/)
set(inc_dir includes/)
set(srcs ${src_dir}main.cpp ${src_dir}pipeline.cpp)

set(headers ${inc_dir}pipeline.hpp)

# OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
  message(STATUS "OpenCV found: ${OpenCV_VERSION}")
  message(STATUS "Include dirs: ${OpenCV_INCLUDE_DIRS}")
  message(STATUS "Libraries: ${OpenCV_LIBS}")
else()
  message(FATAL_ERROR "OpenCV not found. Make sure it's installed.")
endif()

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS} includes)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Library and executable
add_library(first_opencv_lib STATIC ${srcs} ${headers})
add_subdirectory(test)
add_executable(${exec_name} ${srcs})

# Link libraries
target_link_libraries(${exec_name} PRIVATE ${OpenCV_LIBS})
