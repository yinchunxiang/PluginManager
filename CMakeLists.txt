cmake_minimum_required(VERSION 2.8)
project(pluma)

set(project_root_dir ${PROJECT_SOURCE_DIR})
include_directories(${project_root_dir/src})

set(executable_output_path ${project_root_dir}/build/bin)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_COMPLIER "g++")
set(CMAKE_CXX_FLAGS "-fPIC --std=c++11")
#set(CMAKE_CXX_FLAGS "--std=c++11")

file(GLOB so_src "${project_root_dir}/src/plugins/*.h" "${project_root_dir}/src/plugins/*.cpp")
file(GLOB main_src "${project_root_dir}/src/*.h" "${project_root_dir}/src/*.cpp")
add_library(plugin SHARED ${so_src} ${main_src})
target_link_libraries(plugin dl crypto)

add_executable(pluma "${project_root_dir}/src/main.cc" ${main_src})
target_link_libraries(pluma dl crypto pthread)

