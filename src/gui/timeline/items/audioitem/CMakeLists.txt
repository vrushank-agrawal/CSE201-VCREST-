add_library(AudioItem audioitem.cpp audioresizer.cpp)

target_include_directories(AudioItem
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(AudioItem
        QtExternalLibrary
        SizeGripItem
        )