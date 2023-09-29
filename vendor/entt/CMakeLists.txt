project(entt)

file(GLOB_RECURSE header_files
        "*.hpp"
        )

add_library(entt SHARED ${header_files})
set_target_properties(entt PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(entt PUBLIC /)