add_library(imageThumbnail imglist.cpp temp.cpp temp.h temp.ui imagethumbnail.cpp imagethumbnail.h)

target_include_directories(imageThumbnail
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageThumbnail
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )