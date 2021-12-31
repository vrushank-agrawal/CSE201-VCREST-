add_library(imageManager imagemanager.cpp)

target_include_directories(imageManager
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageManager
        imageLibrary
        opencvExternalLibrary
        qtExternalLibrary
        )