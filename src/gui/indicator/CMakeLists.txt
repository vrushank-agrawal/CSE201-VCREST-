add_library(indicator indicator.cpp)

target_include_directories(indicator
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(indicator
        qtExternalLibrary
        )