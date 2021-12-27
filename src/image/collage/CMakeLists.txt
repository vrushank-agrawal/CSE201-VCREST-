add_library( collage collage.cpp)

target_include_directories( collage
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(collage PUBLIC
        opencvExternalLibrary
        )