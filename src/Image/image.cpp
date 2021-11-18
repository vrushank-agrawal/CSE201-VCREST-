//
// Created by Vrushank on 11/12/2021.
//
#include <stdio.h>
#include "image.h"
#include <stdarg.h>

using namespace img;

img::Image::Image(string filename) {
    this -> filename = filename;
    if (this -> validImg( filename )) {
        this -> img_matrix = this ->decodeImg( filename, IMREAD_COLOR);
        if (this -> img_matrix == NULL) {
            string s = 'improper image exception';
            return s;
        }
    } else {
        string s = 'file reading exception';
        return s;
    };
}

img::Image::~Image() {
    delete img_matrix;
    delete filename;
    delete save_filename;
}

bool img::Image::validImg(const string &filename) {
    return haveImageReader(filename);
}

Mat img::Image::getMat(){
    return this -> img_matrix;
}

Mat img::Image::decodeImg(const String &filename, int flags) {
    return imread( filename, IMREAD_COLOR);
}

String img::Image::getFilename() {
    return this -> filename;
}

bool img::Image::saveImg(int filepath) {

}

//
//Mat stitch(int column_div, int row_div, int num,...){
//    // list of row and column divisions in tuples, column divisions list((int left_most_pixel, int right_most_pixel))
//    // num indicates the number of image arguments (probably should be limited to 4 max, which can be called recursively
//    va_list valist;
//    va_start(valist, num);
//    Image image_list[num];
//    Mat output = Mat()
//    for (i = 0; i < num; i++) {
//        int width = column_div[i][1] - column_div[i][0]
//        int height = row_div[i][1] - row_div[i][0]
//        image_list = va_arg(valist, int).resize(width , height);
//   }
//   //use hconcat and vconcat on the list of matrices to create a collage : D
//
//   for
//
//
//
//}
//Mat hstitch(Mat mat1, Mat mat2){
//    //later on we can add the division (currently)
//    Mat output;
//    int out_height = min(mat1.size().height, mat2.size().height);
//    Mat temp1= mat1;
//    Mat temp2= mat2;
//    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
//    temp1.resize(mat1.size().width , out_height);
//    temp2.resize(mat2.size().width, out_height);
//    hconcat(temp1,temp2, output);
//    delete temp1;
//    delete temp2;
//    return output;
//}
//Mat vstitch(Mat mat1, Mat mat2){
//    //later on we can add the division (currently)
//    Mat output;
//    int out_wdith = min(mat1.size().width, mat2.size().width);
//    Mat temp1= mat1;
//    Mat temp2= mat2;
//    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
//    temp1.resize(out_wdith);
//    temp2.resize(out_wdith, mat1.size().height);
//    hconcat(temp1,temp2, mat2.size().height);
//    delete temp1;
//    delete temp2;
//    return output;
//}