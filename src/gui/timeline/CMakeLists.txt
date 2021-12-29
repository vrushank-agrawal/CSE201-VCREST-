add_library(timeline timeline.cpp)

target_include_directories(timeline
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(timeline
        qtExternalLibrary
        audioItem
        indicator
        imageItem
        imageLibrary
        sizeGripItem
        )