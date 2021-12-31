add_library(gui)

add_subdirectory(audioitem)
add_subdirectory(audiomanager)
add_subdirectory(audioplayer)
add_subdirectory(imageitem)
add_subdirectory(imagemanager)
add_subdirectory(indicator)
add_subdirectory(videoplayer)
add_subdirectory(videowindow)
add_subdirectory(progressbar)
add_subdirectory(timeline)
add_subdirectory(sizegripitem)

target_include_directories(gui
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(gui
        audioItem
        audioPlayer
        audioManager
        imageItem
        imageManager
        indicator
        progressBar
        sizeGripItem
        timeline
        videoLibrary
        videoPlayer
        videoWindow
        )