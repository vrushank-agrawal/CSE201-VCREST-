add_library(audioPlayer audioPlayer.cpp)

target_include_directories(audioPlayer
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(audioPlayer
        qtExternalLibrary
        audioItem
        )