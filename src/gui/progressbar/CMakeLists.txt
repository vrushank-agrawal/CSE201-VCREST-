cmake_minimum_required(VERSION 3.20)

add_library(progressBar progressbar.cpp)

target_include_directories(progressBar
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(progressBar
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )