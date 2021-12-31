cmake_minimum_required(VERSION 3.20)

add_subdirectory(aubio)
add_subdirectory(lame)

add_library(AudioLibrary audio.cpp audio.hpp lameHelper.cpp lameHelper.hpp)

target_include_directories(AudioLibrary PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(AudioLibrary PUBLIC
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

find_package(Qt6 COMPONENTS Core REQUIRED)

target_link_libraries(AudioLibrary PUBLIC
        Aubio
        Lame
        Qt6::Core)
