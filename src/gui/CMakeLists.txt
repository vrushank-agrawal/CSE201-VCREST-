add_library(GUI)

add_subdirectory(audiomanager)
add_subdirectory(audioplayer)
add_subdirectory(imagemanager)
add_subdirectory(videoplayer)
add_subdirectory(videowindow)
add_subdirectory(progressbar)
add_subdirectory(timeline)

target_include_directories(GUI
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(GUI
        AudioPlayer
        AudioManager
        ImageManager
        ProgressBar
        Timeline
        VideoPlayer
        VideoWindow
        )