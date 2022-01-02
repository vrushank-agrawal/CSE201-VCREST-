cmake_minimum_required(VERSION 3.20)

add_library(ImageItem imageitem.cpp imageresizer.cpp imageitemmenu.cpp)

target_include_directories(ImageItem
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(ImageItem
        QtExternalLibrary
        ImageLibrary
        SizeGripItem
        VideoLibrary
        )