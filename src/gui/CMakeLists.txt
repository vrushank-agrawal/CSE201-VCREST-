add_library(GUI)

add_subdirectory(audioitem)
add_subdirectory(audiomanager)
add_subdirectory(audioplayer)
add_subdirectory(imageitem)
add_subdirectory(imagemanager)
add_subdirectory(videoplayer)
add_subdirectory(videowindow)
add_subdirectory(progressbar)
add_subdirectory(timeline)
add_subdirectory(sizegripitem)

target_include_directories(GUI
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(GUI
        AudioItem
        AudioPlayer
        AudioManager
        ImageItem
        ImageManager
        ProgressBar
        SizeGripItem
        Timeline
        VideoLibrary
        VideoPlayer
        VideoWindow
        )