add_library(SizeGripItem sizegripitem.cpp)

target_include_directories(SizeGripItem
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(SizeGripItem
        QtExternalLibrary
        )