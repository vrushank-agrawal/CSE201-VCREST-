cmake_minimum_required(VERSION 3.20)

add_library(audio audio.cpp)

target_include_directories(audio
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )