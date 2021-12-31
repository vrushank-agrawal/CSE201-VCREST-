add_library(VideoWindow videowindow.cpp)

target_include_directories(VideoWindow
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(VideoWindow
        QtExternalLibrary
        )