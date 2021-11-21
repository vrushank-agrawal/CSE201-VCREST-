//
// Created by Yao on 13/12/2021.
//
#include "image.h"

using namespace img;
using namespace cv;

void img::Image::rotateImg(double angle){
    Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0); //rotate around the center point as axis
    Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0); //create a rotation matrix with the angle given
    warpAffine(this->imgMatrix, this->imgMatrix, rotationMatrix, image.size()); //update image to be the rotation image
}

void img::Image::resizeImg(int width, int height){
    resize(this->imgMatrix, this->imgMatrix, Size(width, height), INTER_LINEAR); //uses linear interpolation to resize the image.
}