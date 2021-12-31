add_library(audioItem audioitem.cpp audioresizer.cpp)

target_include_directories(audioItem
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(audioItem
        qtExternalLibrary
        sizeGripItem
        )