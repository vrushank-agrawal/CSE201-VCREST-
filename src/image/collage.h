#include "image.h"

#include <iostream>
#include <stdarg.h>

namespace img {

    class Collage {
            public:
                Collage(int numImages, vector<Image> imageArr);
                ~ Collage();

                //create an array of coordinates of corners of each of the images, variable
//                int subImageCorners[numImages * 4];

                void twoStitch();
                void threeStitch();
                void fourStitch();
                void flip();

                int getNumImages();
                const std::vector<double>& getRatios();
                double getMaxRatios();
                const std::vector<Image>& getImageArr();
                int getMaxRatiosIndex();
                Mat getModifiedImage();

            private:

                int numImages;
                vector <double> ratios;
                double maxRatios;
                vector <Image> imageArr;
                int maxRatiosIndex;
                Mat modifiedImage;

    };
}