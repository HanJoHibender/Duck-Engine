cmake_minimum_required(VERSION 3.24)
project(DuckExample)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE src_files
        "Example/*.h"
        "Example/*.cpp")

add_subdirectory("Engine")

add_executable(DuckExample ${src_files})

target_link_libraries(DuckExample PUBLIC DuckEngine)
target_include_directories(DuckExample PUBLIC "Engine/src")
set_target_properties(DuckExample PROPERTIES LINKER_LANGUAGE CXX)