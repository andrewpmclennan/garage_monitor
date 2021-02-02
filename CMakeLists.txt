cmake_minimum_required(VERSION 3.10)

# set the project name
project(Garage_Monitor)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)


# Sets the relative path so that the compile tools can be found. 
if (variable)
	set(CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/../tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-cc)
else()
	set(CMAKE_C_COMPILER /usr/bin/gcc)
endif()

# add executable
add_executable(garage_monitor_client src/garage_client.c)
add_executable(garage_monitor_server src/garage_server.c)
