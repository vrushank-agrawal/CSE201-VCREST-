add_library(imageLibrary image.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_include_directories(imageLibrary
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageLibrary ${OpenCV_LIBS})

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")