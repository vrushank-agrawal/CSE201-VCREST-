#pragma once

#ifndef COLLAGE_CLASS
#define COLLAGE_CLASS

#include "../image.h"
#include <iostream>

namespace img {

    class Collage : public Image {
    public:
        explicit Collage(std::vector<img::Image> imageArr);
        ~ Collage();

        // actual stitching functions
        void twoStitch(bool);
        void threeStitch();
        void fourStitch(bool);
        void fourStitchRec(int times);

        void imgModifiedPreview(const std::string &winname);

        // get and set functions
        [[nodiscard]] int getNumImages() const;
        const std::vector<double> &getRatios();
        const std::vector<img::Image> &getImageArr();
        cv::Mat getModifiedImage();
        void setModifiedImageArr(const std::vector<img::Image>& arrModified);
        std::vector<img::Image> getModifiedImageArr();
        void setModifiedImage(cv::Mat modifiedMat);
        const std::vector<double> &getModifiedRatios();
        void setFourStitchRecImgArr(const cv::Mat& image);
        const std::vector<Image> &getFourStitchRecImgArr();

    private:
        std::vector<Image> fourStitchRecImgArr;
        int numImages;
        int modifiedNumImages{};
        std::vector<double> ratios;
        std::vector<double> modifiedRatios;
        std::vector<img::Image> imageArr;
        cv::Mat modifiedImage;
        std::vector<img::Image> imageArrModified;

        void fourStitchRecAux(bool, int times);
    };
}

#endif // COLLAGE_CLASS