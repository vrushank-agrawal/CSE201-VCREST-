cmake_minimum_required(VERSION 3.20)

add_library(sizeGripItem sizegripitem.cpp)

target_include_directories(sizeGripItem
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(sizeGripItem
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )