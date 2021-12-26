cmake_minimum_required(VERSION 3.20)

add_subdirectory(gui)
add_subdirectory(image)
add_subdirectory(audio)
add_subdirectory(video)

add_library(videoEditor videoeditor.cpp)

target_include_directories(videoEditor
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(videoEditor
        Qt::Core
        Qt::Gui
        Qt::Widgets
        gui
        imageLibrary
        audio
        video
        )