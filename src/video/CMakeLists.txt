cmake_minimum_required(VERSION 3.20)

add_library(videoLibrary video.cpp)

target_include_directories(videoLibrary
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

#add_executable( video test_video.cpp)
target_link_libraries(videoLibrary
        imageLibrary
        opencvExternalLibrary
        )