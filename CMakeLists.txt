cmake_minimum_required(VERSION 3.24)
project(DuckEngine)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE src_files
        "src/*.h"
        "src/*.cpp")


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory("vendor/glfw")
add_subdirectory("vendor/glm")
add_subdirectory("vendor/glad")
add_subdirectory("vendor/stb")
add_subdirectory("vendor/entt")
add_subdirectory("vendor/uuid_v4")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
find_package(Threads REQUIRED)

add_executable(DuckEngine ${src_files})

target_precompile_headers(DuckEngine PRIVATE src/pch.cxx src/pch.hxx)
target_link_libraries(DuckEngine PUBLIC glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES}
        glm glad)
target_include_directories(DuckEngine PUBLIC "vendor" PUBLIC "src")
set_target_properties(DuckEngine PROPERTIES LINKER_LANGUAGE CXX)
