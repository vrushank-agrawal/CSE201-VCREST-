add_library(TimelineItems)

add_subdirectory(audioitem)
add_subdirectory(imageitem)
add_subdirectory(sizegripitem)

target_include_directories(TimelineItems
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(TimelineItems
        AudioItem
        ImageItem
        SizeGripItem
        )