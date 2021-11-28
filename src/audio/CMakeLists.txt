cmake_minimum_required(VERSION 3.20)

add_library(audio audio.cpp audio.hpp)

target_include_directories(audio PUBLIC ../../libs/aubio/include)

target_link_directories(audio PUBLIC ../../libs/aubio/lib)

target_link_libraries(audio PUBLIC libaubio.a)
