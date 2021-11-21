//
// Created by Vrushank on 11/12/2021.
//
#include <stdio.h>
#include "image.h"
#include <stdarg.h>

using namespace img;

img::Image::Image(string filename) {
    this -> filename = filename;
    this -> validImg( filename );
}

bool img::Image::validImg(const string &filename) {


}

Mat img::Image::getMat(){
    
}
double img::Image::getRatio(){
    size dimensions = imgMatrix.size();
    return dimensions.height/ dimensions.width;
}
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
