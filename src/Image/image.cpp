//
// Created by Vrushank on 11/12/2021.
//

#include "image.h"

using namespace img;

img::Image::Image(string filename) {
    this -> filename = filename;
    this -> validImg( filename );
}

bool img::Image::validImg(const string &filename) {


}

Mat img::Image::getMat(){

}

