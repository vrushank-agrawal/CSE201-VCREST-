//
// Created by Vrushank on 11/12/2021.
//

#include "image.h"

img::Image::Image() {}

img::Image::Image(cv::Mat mat) {
    img_matrix = mat;
    img_matrix_modified = img_matrix.clone();
    filename = std::string();
}

img::Image::Image(const std::string & file) {
    filename = file;
    if (validImg( filename )) {
        img_matrix = decodeImg( filename, cv::IMREAD_COLOR);
        if ( getMat().empty()) {
//            printf("improper image exception - file is corrupt/invalid") ;
            return_img_error(1) ;
        }
    } else {
//        printf("file reading exception - file cannot be read by VEST") ;
        return_img_error(2) ;
    }
    img_matrix_modified = img_matrix.clone();

//        printf("img is valid can be read") ;
    return_img_error(0) ;
}

img::Image::~Image() {}

int img::Image::return_img_error (int val) {
    return val;
}

bool img::Image::validImg(const std::string &filename) {
    return cv::haveImageReader(filename);
}

cv::Mat img::Image::getMat(){
    return this -> img_matrix;
}

cv::Mat img::Image::getModifiedImg() {
    return this-> img_matrix_modified;
}

void img::Image::setModifiedImg(cv::Mat matrix) {
    this -> img_matrix_modified = matrix;
}

cv::Mat img::Image::decodeImg(const std::string &filename, int flags) {
    return imread( filename, cv::IMREAD_COLOR);
}

std::string img::Image::getFilename() {
    return this -> filename;
}

double img::Image::getRatio(){
    return  (1.0* this -> getMat().size().height)/ (1.0 * this -> getMat().size().width);
}

double img::Image::getModifiedImageRatio() {
    return this -> getModifiedImg().size().height/ this -> getModifiedImg().size().width;
}

void img::Image::imgPreview(const std::string &window) {
    cv::Mat mat = this -> getMat();
    imshow(window, mat);
}

void img::Image::imgModifiedPreview(const std::string &window) {
    cv::Mat mat = this -> getModifiedImg();
    imshow(window, mat);
}