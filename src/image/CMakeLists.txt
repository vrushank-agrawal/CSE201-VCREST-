add_library(imageLibrary image.cpp blurs.cpp)

add_subdirectory(collage)

target_include_directories(imageLibrary
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageLibrary
        collage
        opencvExternalLibrary
        )