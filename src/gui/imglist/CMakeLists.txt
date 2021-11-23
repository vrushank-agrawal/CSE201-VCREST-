add_library(imgList imglist.cpp)

target_include_directories(imgList
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imgList
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )