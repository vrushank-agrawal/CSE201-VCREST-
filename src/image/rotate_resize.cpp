//
// Created by Yao on 13/12/2021.
//
#include "image.h"

using namespace img;
using namespace cv;
//
void img::Image::rotateImg(double angle){
    Point2f center((this->getModifiedImg().cols - 1) / 2.0, (this->getModifiedImg().rows - 1) / 2.0); //rotate around the center point as axis
    Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0); //create a rotation matrix with the angle given
    warpAffine(this->getModifiedImg(), this->getModifiedImg(), rotation_matix, this->getMat().size()); //update image to be the rotation image
}

void img::Image::resizeImg(int width, int height) {
    Mat resized_img;
    if (height != 0 && width != 0) {
        resize(this->getModifiedImg(), resized_img, Size(width, height),INTER_LINEAR); //uses linear interpolation to resize the image.
    }
    this ->setModifiedImg(resized_img);
}