//
// Created by Yao on 13/12/2021.
//
#include "image.h"

using namespace img;
using namespace cv;
//
void img::Image::rotateImg(double angle){
    //rotate around the center point as axis
    Point2f center((this->getModifiedImg().cols - 1) / 2.0, (this->getModifiedImg().rows - 1) / 2.0);
    //create a rotation matrix with the angle given
    Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    //update image to be the rotation image
    warpAffine(this->getModifiedImg(), this->getModifiedImg(), rotation_matrix, this->getMat().size());
}

void img::Image::resizeImg(int width, int height) {
    Mat resized_img;
    if (height != 0 && width != 0) {
        //uses linear interpolation to resize the image.
        resize(this->getModifiedImg(), resized_img, Size(width, height),INTER_LINEAR);
    }
    this ->setModifiedImg(resized_img);
}