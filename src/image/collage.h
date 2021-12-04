#include "image.h"

#include <iostream>
#include <stdarg.h>

namespace img {

    class Collage {
            public:
                Collage( vector<Image> imageArr);
                ~ Collage();

                //create an array of coordinates of corners of each of the images, variable
//                int subImageCorners[numImages * 4];

                void twoStitch();
                void threeStitch();
                void fourStitch();
                void flip();

                const std::vector<int>& testVect();
                int getNumImages();
                const std::vector<double>& getRatios();
                const std::vector<Image>& getImageArr();
                Mat getModifiedImage();
                void setModifiedImageArr(vector <Image> imageArrModified);
                vector<Image> getModiefiedImageArr();
                void setModifiedImage(Mat modifiedMat);
            private:

                int numImages;
                vector <double> ratios;

                vector <Image> imageArr;
                int maxRatiosIndex = 0;
                Mat modifiedImage;
                vector <Image> imageArrModified;

    };
}