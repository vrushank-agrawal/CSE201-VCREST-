add_subdirectory(imglist)
add_library(gui videoeditor.cpp)

target_include_directories(gui
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(gui
        Qt::Core
        Qt::Gui
        Qt::Widgets
        imgList
        )