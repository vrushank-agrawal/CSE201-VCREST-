cmake_minimum_required(VERSION 3.0)

project(lame_enc)

set(SOURCE_LIB
        ${CMAKE_CURRENT_SOURCE_DIR}/BladeMP3EncDLL.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCE_LIB})

target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )

TARGET_LINK_LIBRARIES(${PROJECT_NAME} mp3lame)

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)