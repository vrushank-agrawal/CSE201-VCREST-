//
// Created by Vrushank on 11/12/2021.
//

#ifndef IMAGEFILES
#define IMAGEFILES

#include "image.h"
#include "collage/collage.cpp"
#include "blurs.cpp"
#include "rotate_resize.cpp"

#endif

using namespace img;

img::Image::Image() {

}

img::Image::Image(Mat mat) {
    img_matrix = mat;
    img_matrix_modified = img_matrix.clone();
    filename = std::string();
}

img::Image::Image(const string & file) {
    filename = file;
    if (validImg( filename )) {
        img_matrix = decodeImg( filename, IMREAD_COLOR);
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

bool img::Image::validImg(const string &filename) {
    return haveImageReader(filename);
}

Mat img::Image::getMat(){
    return this -> img_matrix;
}

Mat img::Image::getModifiedImg() {
    return this-> img_matrix_modified;
}

void img::Image::setModifiedImg(Mat matrix) {
    this -> img_matrix_modified = matrix;
}

Mat img::Image::decodeImg(const String &filename, int flags) {
    return imread( filename, IMREAD_COLOR);
}

String img::Image::getFilename() {
    return this -> filename;
}

double img::Image::getRatio(){
    return  (1.0* this -> getMat().size().height)/ (1.0 * this -> getMat().size().width);
}

double img::Image::getModifiedImageRatio() {
    return this -> getModifiedImg().size().height/ this -> getModifiedImg().size().width;
}

void img::Image::imgPreview(const String &window) {
    Mat mat = this -> getMat();
    imshow(window, mat);
}

void img::Image::imgModifiedPreview(const string &window) {
    Mat mat = this -> getModifiedImg();
    imshow(window, mat);
}

