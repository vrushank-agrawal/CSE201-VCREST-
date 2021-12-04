cmake_minimum_required(VERSION 3.20)

add_library(imageItem imageitem.cpp)

target_include_directories(imageItem
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageItem
        Qt::Core
        Qt::Gui
        Qt::Widgets
        imageLibrary
        )