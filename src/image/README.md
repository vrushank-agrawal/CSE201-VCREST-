## General Note
The target files for CMake in this directory is `image.cpp` and `blurs.cpp`. 
Both of these files call the `img` namespace and class which are defined in `image.h`.
CMake also calls the subdirectory in collage, details for which are explained in the corresponding folder.

## Image class

As the name suggests, this class works with all individual image manipulation needed by the software.

__Utility__:
- Define OpenCV header files and relevant functions
- Read / Write functions to manipulate images as matrices
- Basic editing functions like resize, rotate, superimpose images
- Basic blurs and filters
- Equalize dimensions of all images by adding black matrix
- Calls default_images in the corresponding folder