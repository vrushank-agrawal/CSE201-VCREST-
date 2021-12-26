cmake_minimum_required(VERSION 3.20)

add_library(exportLibrary export.cpp)

target_include_directories(exportLibrary
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )