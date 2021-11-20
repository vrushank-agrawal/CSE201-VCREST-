//
// Created by Yao on 13/12/2021.
//
#include "image.h"

using namespace img;
using namespace cv;

bool img::Image::saveImg(const string &filepath, InputArray mat, const std::vector<int> &params){
    //eg: "D:path_to_file/image_name.file_type"
    return imwrite(filepath, this->img_matrix);
}