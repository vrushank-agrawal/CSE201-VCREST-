add_library(ImageLibrary image.cpp blurs.cpp)

add_subdirectory(collage)

target_include_directories(ImageLibrary
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(ImageLibrary
        Collage
        OpenCVExternalLibrary
        )