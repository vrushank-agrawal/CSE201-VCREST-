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

                void twoStitch(bool );
                void threeStitch();
                void fourStitch(bool );
                void fourStitchRec(int times);
                void flip();

                const std::vector<int>& testVect();
                int getNumImages();
                const std::vector<double>& getRatios();
                const std::vector<Image>& getImageArr();
                Mat getModifiedImage();
                void setModifiedImageArr(vector <Image> imageArrModified);
                vector<Image> getModifiedImageArr();
                void setModifiedImage(Mat modifiedMat);
                const std::vector<double>& getModifiedRatios();
            private:

                int numImages;
                int modifiedNumImages;
                vector <double> ratios;
                vector <double> modifiedRatios;
                vector <Image> imageArr;
                Mat modifiedImage;
                vector <Image> imageArrModified;
                void fourStitchRecAux(bool, int times);

    };
}