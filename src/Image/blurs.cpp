//
// Created by Yao on 13/12/2021.
//
#include "image.h"

using namespace img;
using namespace cv;

// Using open cv build-ins modify the image class's img_matrix 
// Height and width in most cases is to determine the kernel sizes, too big, whole image is blurred,
// too small noise remains in the image.

void img::Image::blur(int width, int height){
    cv::blur(this->getMat(), this->getModifiedImg(), Size(width, height));
}

void img::Image::bilateralFilter(int distance) {
    cv::bilateralFilter(this->getMat(), this->getModifiedImg(), distance, distance * 2, distance / 2);
}

void img::Image::boxBlur(int width, int height, int ddepth = -1){
    cv::boxFilter(this->getMat(), this->getModifiedImg(), ddepth, Size(width, height));
};

void img::Image::gaussianBlur(int width, int height){
    if (width % 2 == 0) {
        width --;
    } if (height % 2 == 0) {
        height --;
    }

    GaussianBlur(this->getMat(), this->getModifiedImg(), Size(width, height), 0);
};
void img::Image::medianBlur(int kernel_size){
    if (kernel_size % 2 == 0) {
        kernel_size --;
    }
    cv::medianBlur(this->getMat(), this->getModifiedImg(), kernel_size);
};

