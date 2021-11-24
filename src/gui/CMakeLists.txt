cmake_minimum_required(VERSION 3.20)

add_subdirectory(videoplayer)
add_subdirectory(imagethumbnail)

add_library(gui videoeditor.cpp)

target_include_directories(gui
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(gui
        Qt::Core
        Qt::Gui
        Qt::Widgets
        videoPlayer
        imageThumbnail
        )