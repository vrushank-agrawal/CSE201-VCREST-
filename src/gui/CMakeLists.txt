cmake_minimum_required(VERSION 3.20)

add_subdirectory(videoplayer)
add_subdirectory(videowindow)
add_subdirectory(imagethumbnail)
add_subdirectory(audiomanager)
add_subdirectory(progressbar)

add_library(gui progressbar/progressbar.cpp progressbar/progressbar.h)

target_include_directories(gui
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(gui
        videoPlayer
        videoWindow
        imageThumbnail
        audioManager
        progressBar
        )