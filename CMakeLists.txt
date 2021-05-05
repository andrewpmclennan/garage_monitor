cmake_minimum_required(VERSION 3.10)

include_directories(inc)

# set the project name
project(Garage_Monitor)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
include(CMakePrintHelpers)
cmake_print_variables(arm_compile)

# Sets the relative path so that the compile tools can be found. 
if (arm_compile STREQUAL "ARM")
	set(CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/../tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-cc)
	set(CMAKE_C++_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/../tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

elseif(arm_compile STREQUAL "GCC")
	set(CMAKE_C_COMPILER /usr/bin/gcc)

elseif(arm_compile STREQUAL "TEST")
    set(CMAKE_C_COMPILER /usr/bin/gcc)
    
endif()

add_executable(garage_monitor_client src/garage_client.cpp src/messageStructure.cpp src/clientConnection.cpp)
add_executable(garage_monitor_server src/garage_server.cpp )
add_executable(messageStructure_test test/messageStructureTest.cpp src/messageStructure.cpp src/clientConnection.cpp)



