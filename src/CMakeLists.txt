add_library(videoEditor videoeditor.cpp)

add_subdirectory(gui)
add_subdirectory(image)
add_subdirectory(audio)
add_subdirectory(video)

target_include_directories(videoEditor
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(videoEditor PUBLIC
        gui
        imageLibrary
        audio
        video
        qtExternalLibrary
        opencvExternalLibrary
        )