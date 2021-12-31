add_library(AudioPlayer audioplayer.cpp)

target_include_directories(AudioPlayer
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(AudioPlayer
        QtExternalLibrary
        AudioItem
        AudioManager
        Timeline
        )