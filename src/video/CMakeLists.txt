cmake_minimum_required(VERSION 3.20)

add_library(video video.cpp)

target_include_directories(gui
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

#project( test_video.cpp )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

#add_executable( video test_video.cpp)
target_link_libraries(video
        ${OpenCV_LIBS}
        imageLibrary
        )
