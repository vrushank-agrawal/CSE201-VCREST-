add_library(VideoEditor
        audio.cpp
        export.cpp
        image.cpp
        import.cpp
        menu.cpp
        setup.cpp
        videoeditor.cpp
        )

add_subdirectory(gui)
add_subdirectory(image)
add_subdirectory(audio)
add_subdirectory(video)
add_subdirectory(export)

target_include_directories(VideoEditor
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(VideoEditor PUBLIC
        GUI
        ImageLibrary
        AudioLibrary
        VideoLibrary
        ExportLibrary
        QtExternalLibrary
        OpenCVExternalLibrary
        )