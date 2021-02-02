cmake_minimum_required(VERSION 3.10)

# set the project name
project(Garage_Monitor)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# add executable
add_executable(garage_monitor_server src/hello.c)
