cmake_minimum_required(VERSION 3.20)

add_library(audio audio.cpp audio.hpp lameHelper.cpp lameHelper.hpp)

target_include_directories(audio PUBLIC
        ../../libs/lame/include
        ../../libs/aubio/include
        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(audio PUBLIC
        ../../libs/lame/lib
        ../../libs/aubio/lib
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(audio PUBLIC libaubio.a libmp3lame.a)
