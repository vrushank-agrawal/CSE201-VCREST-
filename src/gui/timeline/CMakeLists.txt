add_library(Timeline
        audio.cpp
        image.cpp
        timeline.cpp
        )

target_include_directories(Timeline
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(Timeline
        QtExternalLibrary
        AudioItem
        Indicator
        ImageItem
        ImageLibrary
        SizeGripItem
        )