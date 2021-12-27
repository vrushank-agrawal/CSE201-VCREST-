add_library(gui)

add_subdirectory(videoplayer)
add_subdirectory(videowindow)
add_subdirectory(imagethumbnail)
add_subdirectory(audiomanager)
add_subdirectory(progressbar)
add_subdirectory(timeline)
add_subdirectory(indicator)
add_subdirectory(imageitem)
add_subdirectory(sizegripitem)
add_subdirectory(imageitemmenu)

target_include_directories(gui
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(gui
        videoPlayer
        videoWindow
        imageThumbnail
        audioManager
        progressBar
        timeline
        indicator
        imageItem
        sizeGripItem
        imageItemMenu
        video
        )