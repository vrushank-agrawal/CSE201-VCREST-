add_library(videoPlayer videoplayer.cpp)

target_include_directories(videoPlayer
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(videoPlayer
        opencvExternalLibrary
        qtExternalLibrary
        videoWindow
        )