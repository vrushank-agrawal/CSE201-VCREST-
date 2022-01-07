add_library(VideoPlayer videoplayer.cpp videowindow.cpp)

target_include_directories(VideoPlayer
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(VideoPlayer
        OpenCVExternalLibrary
        QtExternalLibrary
        )