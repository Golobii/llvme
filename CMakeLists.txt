cmake_minimum_required(VERSION 3.10)

# set the project name
project(llvme)

file(GLOB src "src/*.cpp" "src/**/*.cpp")

include_directories(/usr/include)
link_directories(/usr/lib)


# add the executable
add_executable(llvme ${src})

target_link_libraries(llvme ncurses)
