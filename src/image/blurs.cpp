//
// Created by Yao on 13/12/2021.
//

// Using open cv build-ins modify the image class's img_matrix
// Height and width in most cases is to determine the kernel sizes,
// too big, whole image is blurred, too small noise remains in the image.

#include "image.h"


void img::Image::blur(int width, int height){
    if (width && height) {
        cv::Mat temp = this -> getModifiedImg();
        cv::blur(temp, temp, cv::Size(width, height));
        this -> setModifiedImg( temp );
    }
}

void img::Image::bilateralFilterPreview(int distance) {
    if (distance) {
        cv::Mat temp = (this->getModifiedImg()).clone();
        cv::Mat tempOut;
        cv::bilateralFilter(temp, tempOut, distance , distance * 2, distance / 2);
        this->setBilateralFilterImg(tempOut);
    }
}

void img::Image::bilateralFilter(int distance) {
    if (distance) {
        cv::Mat temp;
        cv::bilateralFilter(this->getModifiedImg(), temp, distance, distance * 2, distance / 2);
        this ->setModifiedImg( temp );
    }
}

void img::Image::boxBlur(int width, int height, int depth = -1){
    if (width && height)
        cv::boxFilter(this->getModifiedImg(), img_matrix_modified, depth, cv::Size(width, height));
}

void img::Image::gaussianBlur(int width, int height){
    // fix height and width as necessary
    if (!(width & 1) && width) width --;
    if (!(height & 1) && height) height --;

    if (width && height)
        cv::GaussianBlur(this->getModifiedImg(), img_matrix_modified, cv::Size(width, height), 0);
}

void img::Image::medianBlur(int kernel_size){
    if (!(kernel_size & 1)) kernel_size-- ;
    if (kernel_size)
        cv::medianBlur(this->getModifiedImg(), img_matrix_modified, kernel_size);
}

void img::Image::rotateImg(double angle) {
    //rotate around the center point as axis
    cv::Point2f center((this->getModifiedImg().cols - 1) / 2.0, (this->getModifiedImg().rows - 1) / 2.0);
    //create a rotation matrix with the angle given
    cv::Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    //update image to be the rotation image
    warpAffine(this->getModifiedImg(), img_matrix_modified, rotation_matrix, img_matrix_modified.size());
}

void img::Image::rotateImgFit(double angle) {
    //rotate around the center point as axis
    cv::Point2f center((img_matrix_modified.cols - 1) / 2.0, (img_matrix_modified.rows - 1) / 2.0);
    //create a rotation matrix with the angle given
    cv::Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), img_matrix_modified.size(), angle).boundingRect2f();
    // adjust transformation matrix
    rotation_matrix.at<double>(0,2) += bbox.width/2.0 - img_matrix_modified.cols/2.0;
    rotation_matrix.at<double>(1,2) += bbox.height/2.0 - img_matrix_modified.rows/2.0;
    //update image to be the rotation image
    warpAffine(this->getModifiedImg(), img_matrix_modified, rotation_matrix, bbox.size());
    warpAffine(this->getCurrentUnblurImg(), current_unblur_matrix, rotation_matrix, bbox.size());
}

void img::Image::resizeImg(int width, int height) {
    cv::Mat resized_img;
    if (height && width) {
        //uses linear interpolation to resize the image.
        resize(this->getModifiedImg(), resized_img, cv::Size(width, height),cv::INTER_LINEAR);
    }
    this ->setModifiedImg(resized_img);
}