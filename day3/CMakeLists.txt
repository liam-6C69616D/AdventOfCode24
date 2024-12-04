# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyCProject C)

# Set C standard (optional, but recommended)
set(CMAKE_C_STANDARD 99)

# Add the source files (list all .c files)
set(SOURCE_FILES_Puzzle1 src/puzzle1.c)
set(SOURCE_FILES_Puzzle2 src/puzzle2.c)

# Add the include directory
include_directories(include)

# Create an executable from the source files
add_executable(puzzle1 ${SOURCE_FILES_Puzzle1})
add_executable(puzzle2 ${SOURCE_FILES_Puzzle2})
