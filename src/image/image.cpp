//
// Created by Vrushank on 11/12/2021.
//

#include "image.h"

img::Image::Image() {}

img::Image::Image(cv::Mat mat) {
    img_matrix = mat;
    current_unblur_matrix = img_matrix.clone();
    img_matrix_modified = img_matrix.clone();
    filename = "no file path provided";
}

img::Image::Image(const std::string & file) {
    filename = file;
    if (validImg( filename )) {
        img_matrix = decodeImg( filename, cv::IMREAD_COLOR);
        if ( getMat().empty()) {
            return_img_error(1) ; //"improper image exception - file is corrupt/invalid")
        }
    } else {
        return_img_error(2) ; //printf("file reading exception - file cannot be read by VEST")
    }
    img_matrix_modified = img_matrix.clone();
    return_img_error(0) ; //printf("img is valid can be read")
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

void img::Image::setOriginalImg(cv::Mat matrix) {
    this -> img_matrix = matrix;
}

void img::Image::setBilateralFilterImg(cv::Mat matrix) {
    this -> img_matrix_bilateralFilter = matrix;
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

int img::Image::getHeight () {
    return this -> getMat().size().height;
}

int img::Image::getWidth() {
    return this -> getMat().size().width;
}

int img::Image::getModifiedHeight() {
    return this -> getModifiedImg().size().height;
}

int img::Image::getModifiedWidth() {
    return this -> getModifiedImg().size().width;
}

// adds black areas to image
void img::Image::equalizeImgDim( double width, double height) {
    double fixedRatio = height / width;
    double imgRatio = this -> getRatio();

    // just resizing works
    if (imgRatio == fixedRatio) {
        this->resizeImg(width, height);
        return;
    }

    // change image because ratios are different
    if (( imgRatio > fixedRatio ) ) {
        if ( this -> getModifiedHeight() > height ) {

            // calculate new width for the image
            int new_width = std::floor( this -> getModifiedWidth() * height / this -> getModifiedHeight() );
            this ->resizeImg( new_width, height );

            // get the width of black image
            int black_width = floor( abs(width - new_width) / 2 );

            // create black image and resize it
            Image Black = img::Image(blackMat);
            Black.resizeImg( black_width, height );
            Image* blackptr = &Black;

            // adding black matrices
            // resizing image again
            this -> sendToStitch( 0, blackptr );
            this -> resizeImg(width, height);

            return;
        } else if (this -> getModifiedHeight() < height) {

            // calculate new width for the image
            int new_width = std::floor( this -> getModifiedWidth() * height / this -> getModifiedHeight() );
            this ->resizeImg( new_width, height );

            // get the width of black image
            int black_width = floor( abs(width - new_width) / 2 );

            // create black image and resize it
            Image Black = img::Image(blackMat);
            Image* blackptr = &Black;
            Black.resizeImg( black_width, height );

            // adding black matrices
            // resizing image again
            this -> sendToStitch( 0, blackptr );
            this -> resizeImg(width, height);

            return;
        }
    }
    if (( imgRatio < fixedRatio ) ) {
        if ( this -> getModifiedWidth() > width ) {

            // calculate new height for the image
            int new_height = std::floor( this -> getModifiedHeight() * width / this -> getModifiedWidth() );
            this -> resizeImg( width, new_height );

            // get the width of black image
            int black_height = floor( abs(height - new_height) / 2 );

            // create black image and resize it
            Image Black = img::Image(blackMat);
            Black.resizeImg( width, black_height );
            Image* blackptr = &Black;

            // adding black matrices
            // resizing image again
            this -> sendToStitch( 1, blackptr );
            this -> resizeImg(width, height);

            return;
        } else if (this -> getModifiedWidth() < width) {

            // calculate new height for the image
            int new_height = std::floor( this -> getModifiedHeight() * width / this -> getModifiedWidth() );
            this -> resizeImg( width, new_height );

            // get the width of black image
            int black_height = floor( abs(height - new_height) / 2 );

            // create black image and resize it
            Image Black = img::Image(blackMat);
            Black.resizeImg( width, black_height );
            Image* blackptr = &Black;

            // adding black matrices
            // resizing image again
            this -> sendToStitch( 1, blackptr );
            this -> resizeImg(width, height);

            return;
        }
    }
}

void img::Image::sendToStitch(int val, Image *img) {
    if (val == 0) {
        this ->hcon( img );
    } else if ( val == 1) {
        this -> vcon( img );
    }
}

void img::Image::hcon(Image *black) {
    cv::Mat out;
    cv::hconcat(black -> getModifiedImg(), this -> getModifiedImg(), out);
    cv::hconcat(out, black -> getModifiedImg(), out);

    this ->setModifiedImg( out );
}

void img::Image::vcon(Image *black) {
    cv::Mat out;
    cv::vconcat(black -> getModifiedImg(), this -> getModifiedImg(), out);
    cv::vconcat(out, black -> getModifiedImg(), out);

    this ->setModifiedImg( out );
}

cv::Mat img::Image::getCurrentUnblurImg() {
    return this->current_unblur_matrix;
}

void img::Image::setCurrentUnblurImg(cv::Mat mat) {
    this->current_unblur_matrix = mat;
}
