add_library(imageItemMenu imageitemmenu.cpp)

target_include_directories(imageItemMenu
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageItemMenu
        Qt::Core
        Qt::Gui
        Qt::Widgets
        video
        )