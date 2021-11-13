//
// Created by Yao on 13/12/2021.
//
#include "image.h"

using namespace img;
using namespace cv;

void img::Image::rotateImg(double angle){
    Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0); //rotate around the center point as axis
    Mat rotation_matix = getRotationMatrix2D(center, angle, 1.0); //create a rotation matrix with the angle given
    warpAffine(this->img_matrix, this->img_matrix, rotation_matix, image.size()); //update image to be the rotation image
}

void img::Image::resizeImg(int width, int height){
    resize(this->img_matrix, this->img_matrix, Size(width, height), INTER_LINEAR); //uses linear interpolation to resize the image.
}