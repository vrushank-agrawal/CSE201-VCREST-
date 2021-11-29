cmake_minimum_required(VERSION 3.20)

add_library(videoWindow videowindow.cpp)

target_include_directories(videoWindow
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(videoWindow
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )