The target files for CMake in this directory is image.cpp and blurs.cpp. 
Both of these files call the image namespace and class which are defined in image.h.
CMake also calls the subdirectory in collage folder which is explained in the file.
The image class provides all functions on images from reading and writing to editing and animating used in the GUI and video animations respectively.
The OpenCV files required for the project are also included in these files and can be changed from here only.
The default_images folder contains images to be added in the GUI 