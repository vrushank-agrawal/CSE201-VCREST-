cmake_minimum_required(VERSION 3.20)

add_library(timeline timeline.cpp)

target_include_directories(timeline
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(timeline
        Qt::Core
        Qt::Gui
        Qt::Widgets
        indicator
        imageItem
        imageLibrary
        )