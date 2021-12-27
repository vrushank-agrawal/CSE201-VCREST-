add_library(imageItemMenu imageitemmenu.cpp)

target_include_directories(imageItemMenu
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(imageItemMenu
        qtExternalLibrary
        video
        )