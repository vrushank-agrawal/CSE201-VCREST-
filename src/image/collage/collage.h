#pragma once

#include "../image.h"
#include <iostream>

using cv::Mat;
using std::vector;
using img::Image;

#ifndef COLLAGE_CLASS
#define COLLAGE_CLASS

namespace img {

    class Collage {
            public:
                Collage( vector<Image> imageArr);
                ~ Collage();

                //create an array of coordinates of corners of each of the images, variable
                //int subImageCorners[numImages * 4];

                void twoStitch(bool );
                void threeStitch();
                void fourStitch(bool );
                void fourStitchRec(int times);

                // creates inline stitching for black image adding
                void threeStitchInline(int val);
                void flip();

                const std::vector<int>& testVect();
                int getNumImages();
                const std::vector<double>& getRatios();
                const std::vector<Image>& getImageArr();
                Mat getModifiedImage();
                void imgModifiedPreview( const std::string & winname);
                void setModifiedImageArr(vector<Image> imageArrModified);
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

#endif // COLLAGE_CLASS