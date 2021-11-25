add_library(audioManager audiomanager.cpp)

target_include_directories(audioManager
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(audioManager
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )