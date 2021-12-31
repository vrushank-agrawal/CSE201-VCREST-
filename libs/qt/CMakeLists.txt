add_library(qtExternalLibrary INTERFACE)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

target_link_libraries(qtExternalLibrary INTERFACE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Multimedia
        )