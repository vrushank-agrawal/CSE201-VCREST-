add_library(progressBar progressbar.cpp)

target_include_directories(progressBar
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(progressBar
        qtExternalLibrary
        )