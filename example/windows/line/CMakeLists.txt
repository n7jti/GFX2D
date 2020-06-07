cmake_minimum_required(VERSION 3.10)

# set the project name
project(line, CXX)

# add the executable
add_executable(line main.cc)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)