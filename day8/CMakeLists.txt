# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the project name and programming language
project(MyProject VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# Add an executable target
add_executable(puzzle1 src/puzzle1.cpp)
add_executable(puzzle2 src/puzzle2.cpp)

