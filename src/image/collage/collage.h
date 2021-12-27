#pragma once

#include "../image.h"
#include <iostream>

#ifndef COLLAGE_CLASS
#define COLLAGE_CLASS

namespace img {

    class Collage {
            public:
                Collage( std::vector<img::Image> imageArr);
                ~ Collage();

                //create an array of coordinates of corners of each of the images, variable
                //int subImageCorners[numImages * 4];

                void twoStitch(bool );
                void threeStitch();
                void fourStitch(bool );
                void fourStitchRec(int times);

                void imgModifiedPreview( const std::string & winname);

                // get and set functions
                int getNumImages();
                const std::vector<double>& getRatios();
                const std::vector<img::Image>& getImageArr();
                cv::Mat getModifiedImage();
                void setModifiedImageArr(std::vector<img::Image> imageArrModified);
                std::vector<img::Image> getModifiedImageArr();
                void setModifiedImage(cv::Mat modifiedMat);
                const std::vector<double>& getModifiedRatios();

            private:

                int numImages;
                int modifiedNumImages;
                std::vector <double> ratios;
                std::vector <double> modifiedRatios;
                std::vector <img::Image> imageArr;
                cv::Mat modifiedImage;
                std::vector <img::Image> imageArrModified;
                void fourStitchRecAux(bool, int times);
    };
}

#endif // COLLAGE_CLASS