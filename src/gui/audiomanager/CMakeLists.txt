add_library(AudioManager audiomanager.cpp)

target_include_directories(AudioManager
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(AudioManager
        AudioLibrary
        QtExternalLibrary
        )