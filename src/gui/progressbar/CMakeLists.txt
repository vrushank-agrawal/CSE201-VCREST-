add_library(ProgressBar progressbar.cpp)

target_include_directories(ProgressBar
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(ProgressBar
        QtExternalLibrary
        )