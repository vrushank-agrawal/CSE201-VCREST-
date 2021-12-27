cmake_minimum_required(VERSION 3.20)

project( test_image.cpp )

add_executable( test_image_class test_image.cpp )

target_link_libraries( test_image_class
        opencvExternalLibrary
        )
