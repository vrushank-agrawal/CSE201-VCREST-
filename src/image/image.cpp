//
// Created by Vrushank on 11/12/2021.
//
#include <stdio.h>
#include "image.h"
#include <stdarg.h>

using namespace img;

img::Image::Image(const string & filename) {
    this -> filename = filename;
    if (this -> validImg( filename )) {
        this -> img_matrix = this ->decodeImg( filename, IMREAD_COLOR);
        if ( this -> getMat().empty()) {
//            printf("improper image exception - file is corrupt/invalid") ;
            return_img_error(1) ;
        }
    } else {
//        printf("file reading exception - file cannot be read by VEST") ;
        return_img_error(2) ;
    }
    this -> img_matrix_modified = this -> img_matrix.clone();

//        printf("img is valid can be read") ;
    return_img_error(0) ;
}

img::Image::~Image() {

}

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
            Size dimensions = this -> getMat().size();
            return dimensions.height/ dimensions.width;
        }

void img::Image::imgPreview(const String &window) {
    Mat mat = this -> getMat();
    imshow(window, mat);
}

void img::Image::imgModifiedPreview(const string &window) {
    Mat mat = this -> getModifiedImg();
    imshow(window, mat);
}

//
//bool img::Image::saveImg(int filepath) {
//
//}
