add_library(imageThumbnail imagethumbnail.cpp)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

target_include_directories(imageThumbnail
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageThumbnail
        Qt::Core
        Qt::Gui
        Qt::Widgets
        imageLibrary
        )