add_library(audioManager audiomanager.cpp)

target_include_directories(audioManager
        INTERFACE .
        )

target_link_libraries(audioManager
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )