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
            printf("improper image exception") ;
        }
    } else {
        printf("file reading exception") ;
    }
    this -> img_matrix_modified = this -> img_matrix.clone();
}

img::Image::~Image() {

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
<<<<<<< HEAD
double img::Image::getRatio(){
    size dimensions = imgMatrix.size();
    return dimensions.height/ dimensions.width;
}
=======

String img::Image::getFilename() {
    return this -> filename;
}

void img::Image::imgPreview(const String &window) {
    Mat mat = this -> getMat();
    imshow(window, mat);
}

void img::Image::imgModifiedPreview(const string &window) {
    Mat mat = this -> getModifiedImg();
    imshow(window, mat);
>>>>>>> blur
// Mat stitch(int column_div, int row_div, int num,...){ 
//     // list of row and column divisions in tuples, column divisions list((int left_most_pixel, int right_most_pixel))
//     // num indicates the number of image arguments (probably should be limited to 4 max, which can be called recursively
//     va_list valist;
//     va_start(valist, num);
//     Image image_list[num];
//     Mat output = Mat()
//     for (i = 0; i < num; i++) {
//         int width = column_div[i][1] - column_div[i][0]
//         int height = row_div[i][1] - row_div[i][0]
//         image_list = va_arg(valist, int).resize(width , height);
//    }
//    //use hconcat and vconcat on the list of matrices to create a collage : D

//    for 
   
   

// }

//There are only two methods of stitching divide horizontally or vertically in half.
