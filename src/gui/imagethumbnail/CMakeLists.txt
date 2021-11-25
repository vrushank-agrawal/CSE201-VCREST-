add_library(imageThumbnail imagethumbnail.cpp)

target_include_directories(imageThumbnail
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageThumbnail
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )