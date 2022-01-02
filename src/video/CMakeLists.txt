cmake_minimum_required(VERSION 3.20)

add_library(VideoLibrary video.cpp)

target_include_directories(VideoLibrary
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

#add_executable( video test_video.cpp)
target_link_libraries(VideoLibrary
        ImageLibrary
        OpenCVExternalLibrary
        )