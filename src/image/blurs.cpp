//
// Created by Yao on 13/12/2021.
//

// Using open cv build-ins modify the image class's img_matrix
// Height and width in most cases is to determine the kernel sizes,
// too big, whole image is blurred, too small noise remains in the image.

#include "image.h"

#include <string>
#include <unistd.h>
#include <algorithm>

void img::Image::blur(int width, int height) {
    if (width && height) {
        cv::blur(current_unblur_matrix, img_matrix_modified, cv::Size(width, height));
    }
}

void img::Image::bilateralFilterPreview(int distance) {
    if (distance) {
        cv::Mat temp = (this->getModifiedImg()).clone();
        cv::Mat tempOut;
        cv::bilateralFilter(temp, tempOut, distance, distance * 2, distance / 2);
        this->setBilateralFilterImg(tempOut);
    }
}

void img::Image::bilateralFilter(int distance) {
    if (distance) {
        cv::Mat temp;
        cv::bilateralFilter(this->getModifiedImg(), temp, distance, distance * 2, distance / 2);
        this->setModifiedImg(temp);
    }
}

void img::Image::boxBlur(int width, int height, int depth) {
    if (width && height)
        cv::boxFilter(current_unblur_matrix, img_matrix_modified, depth, cv::Size(width, height));
}

void img::Image::gaussianBlur(int width, int height) {
    // fix height and width as necessary
    if (!(width & 1) && width) width--;
    if (!(height & 1) && height) height--;

    if (width && height)
        cv::GaussianBlur(current_unblur_matrix, img_matrix_modified, cv::Size(width, height), 0);
}

void img::Image::medianBlur(int kernel_size) {
    if (!(kernel_size & 1)) kernel_size--;
    if (kernel_size)
        cv::medianBlur(current_unblur_matrix, img_matrix_modified, kernel_size);
}

void img::Image::rotateImg(double angle) {
    //rotate around the center point as axis
    cv::Point2f center((this->getModifiedImg().cols - 1) / 2.0, (this->getModifiedImg().rows - 1) / 2.0);
    //create a rotation matrix with the angle given
    cv::Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    //update image to be the rotation image
    warpAffine(img_matrix_modified, img_matrix_modified, rotation_matrix, img_matrix_modified.size());
}

void img::Image::rotateImgFit(double angle) {
    //rotate around the center point as axis
    cv::Point2f center((img_matrix_modified.cols - 1) / 2.0, (img_matrix_modified.rows - 1) / 2.0);
    //create a rotation matrix with the angle given
    cv::Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), img_matrix_modified.size(), angle).boundingRect2f();
    // adjust transformation matrix
    rotation_matrix.at<double>(0, 2) += bbox.width / 2.0 - img_matrix_modified.cols / 2.0;
    rotation_matrix.at<double>(1, 2) += bbox.height / 2.0 - img_matrix_modified.rows / 2.0;
    //update image to be the rotation image
    warpAffine(img_matrix_modified, img_matrix_modified, rotation_matrix, bbox.size());
    warpAffine(current_unblur_matrix, current_unblur_matrix, rotation_matrix, bbox.size());
}

void img::Image::resizeImg(int width, int height) {
    cv::Mat resized_img;
    if (height && width) {
        //uses linear interpolation to resize the image.
        resize(this->getModifiedImg(), resized_img, cv::Size(width, height), cv::INTER_LINEAR);
        this->setModifiedImg(resized_img);
    }
}


// fadein functions needed for animation
std::string get_curr_dir() {
    char add[256];
    getcwd(add, 256);

    // convert char to string
    std::string address;
    for (int i = 0; i < strlen(add); i++)
        address += add[i];
    return address;
}

void img::Image::addWeighted(double alpha, double beta, double gamma = 0.0) {
    // superimposes image with black images - we will vary intensity to create fade animation 
    if (alpha != 0 && beta != 0) {

        cv::Mat src1, src2, dst;
        std::string add = get_curr_dir();
        std::string address1 =  "\\..\\default_images\\heaven.jpg";
        std::string address2 =  "\\..\\default_images\\black.jpg";
        src1 = cv::imread(cv::samples::findFile(address1));
        src2 = cv::imread(cv::samples::findFile(address2));

        cv::Mat temp = this->getModifiedImg();
        cv::Mat temp2;
        cv::OutputArray output(temp2);
        cv::InputArray inputImg(temp);
        cv::InputArray blackImg(blackMat);
        cv::addWeighted(src1, alpha, src2, beta, gamma, dst);
        this->setModifiedImg(dst);
        std::cout << this -> getModifiedHeight() << std::endl << this -> getModifiedHeight() << std::endl;
    }
}

