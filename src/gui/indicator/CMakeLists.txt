add_library(Indicator indicator.cpp)

target_include_directories(Indicator
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(Indicator
        QtExternalLibrary
        )