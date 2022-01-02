cmake_minimum_required(VERSION 3.20)

add_library(ExportLibrary export.cpp)

target_include_directories(ExportLibrary
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )