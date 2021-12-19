add_library(export export.cpp)

target_include_directories(export
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )