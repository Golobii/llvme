cmake_minimum_required(VERSION 3.10)

# set the project name
project(llvme)

file(GLOB src "src/*.cpp")

# add the executable
add_executable(llvme ${src})
