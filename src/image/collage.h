#include "image.h"

#include <iostream>
#include <stdarg.h>

namespace img {

    class Collage: public Image {
            public:
                Collage(numImages, imageArr);
                Image imageArr[numImages]; //array of image matrices
                int subImageCorners[numImages*4]; //create an array of coordinates of corners of each of the images, variable 
                void twoStitch();
                void threeStitch();
                void fourStitch();
                void flip();

            private:
                int numImages;
                double ratios;
                double max_ratios;
                Image imageArr;
                int max_ratios_index;

    }
}