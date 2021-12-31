add_library(Collage collage.cpp)

target_include_directories(Collage
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(Collage PUBLIC
        OpenCVExternalLibrary
        )