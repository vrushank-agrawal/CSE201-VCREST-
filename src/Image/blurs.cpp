//
// Created by Yao on 13/12/2021.
//
#include "image.h"

using namespace img;
using namespace cv;

// Using open cv build-ins modify the image class's img_matrix 
// Height and width in most cases is is determine the kernel sizes, too big, whole image is blurred, 
// too small noise remains in the image.
void img::Image::blur(int width, int height){
    blur(this->img_matrix, this->img_matrix, Size(width, height));
}

void img::Image::boxBlur(int width, int height, int ddepth = -1){
    //ddepth 
    boxFilter(this->img_matrix, this->img_matrix, Size(width, height), ddepth);
};
void img::Image::gaussianBlur(int width, int height){
    GaussianBlur(this->img_matrix, this->img_matrix, Size(width, height), 0);
};
void img::Image::medianBlur(int kernel_size){
    medianBlur(this->img_matrix, this->img_matrix, kernel_size)
};

