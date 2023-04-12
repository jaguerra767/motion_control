cmake_minimum_required(VERSION 3.24)
project(motion_control)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(ClearCore-library)
add_executable(motion_control main.cpp)

