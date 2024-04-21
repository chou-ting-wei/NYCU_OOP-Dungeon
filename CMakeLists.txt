cmake_minimum_required(VERSION 3.5.0)
project(dungeon)

message(STATUS "Project Directory: ${PROJECT_SOURCE_DIR}")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall -Wextra -Wshadow -Wconversion")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(_LINUX "build the project on Linux" ON) 
if(_LINUX)
    add_compile_definitions(_LINUX)
endif()

aux_source_directory(${CMAKE_SOURCE_DIR}/src DIR_SRC)

add_executable(dungeon ${DIR_SRC})

target_include_directories(dungeon PRIVATE ${CMAKE_SOURCE_DIR}/include)
