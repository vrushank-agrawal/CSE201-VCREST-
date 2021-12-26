add_library( collage collage.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_include_directories( collage
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        ${OpenCV_LIBS}
        )