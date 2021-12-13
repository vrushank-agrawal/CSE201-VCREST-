cmake_minimum_required(VERSION 3.20)

add_library(indicator indicator.cpp)

target_include_directories(indicator
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(indicator
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )