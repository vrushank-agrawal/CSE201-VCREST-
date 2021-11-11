add_library(image image.cpp)

find_package( OpenCV REQUIRED )

include_directories( ${OPENCV_INCLUDE_DIRS}
        )

target_link_libraries(img
        ${OPENCV_LIBS}
        )