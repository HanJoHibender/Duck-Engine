project(stb)

file(GLOB_RECURSE header_files
        "*.h"
        )

add_library(stb SHARED ${header_files})
set_target_properties(stb PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(stb PUBLIC /)