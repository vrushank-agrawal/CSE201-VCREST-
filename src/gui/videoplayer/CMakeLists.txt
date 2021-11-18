cmake_minimum_required(VERSION 3.20)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_library(videoPlayer videoplayer.cpp)

target_include_directories(videoPlayer
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(videoPlayer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

target_link_libraries(videoPlayer ${OpenCV_LIBS})