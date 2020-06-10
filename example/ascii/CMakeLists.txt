cmake_minimum_required(VERSION 3.10)

# set the project name

# add the executable
add_executable(ascii 
    main.cc
    ../../src/gfx2d.cc
)

target_include_directories(ascii PRIVATE "../../inc")

