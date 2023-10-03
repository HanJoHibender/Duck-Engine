project(uuid_v4)

file(GLOB_RECURSE header_files
        "*.h"
        )

add_library(uuid_v4 SHARED ${header_files})
set_target_properties(uuid_v4 PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(uuid_v4 PUBLIC /)