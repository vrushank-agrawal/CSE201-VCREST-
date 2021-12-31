add_library(ImageManager imagemanager.cpp)

target_include_directories(ImageManager
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(ImageManager
        ImageLibrary
        OpenCVExternalLibrary
        QtExternalLibrary
        )