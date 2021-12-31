add_library(VideoEditor videoeditor.cpp)

add_subdirectory(gui)
add_subdirectory(image)
add_subdirectory(audio)
add_subdirectory(video)

target_include_directories(VideoEditor
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(VideoEditor PUBLIC
        GUI
        ImageLibrary
        AudioLibrary
        VideoLibrary
        QtExternalLibrary
        OpenCVExternalLibrary
        )