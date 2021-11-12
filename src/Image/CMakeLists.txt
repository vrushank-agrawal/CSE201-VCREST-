add_library(image image.cpp)

find_package( OpenCV REQUIRED )

include_directories( ${OPENCV_INCLUDE_DIRS} )

target_link_libraries(img ${OPENCV_LIBS} )

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

