cmake_minimum_required(VERSION 3.10)

include_directories(inc)

# set the project name
project(Garage_Monitor)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)


# Sets the relative path so that the compile tools can be found. 
if (variable)
	set(CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/../tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-cc)
	set(CMAKE_C++_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/../tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)
else()
	set(CMAKE_C_COMPILER /usr/bin/gcc)
endif()

# add executable
add_executable(garage_monitor_client src/garage_client.cpp src/messageStructure.cpp)
add_executable(garage_monitor_server src/garage_server.c)
