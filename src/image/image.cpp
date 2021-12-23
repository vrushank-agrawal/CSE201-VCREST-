//
// Created by Vrushank on 11/12/2021.
//

#include "image.h"

img::Image::Image() {}

img::Image::Image(cv::Mat mat) {
    img_matrix = mat;
    img_matrix_modified = img_matrix.clone();
    filename = "no file path provided";
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

std::string img::Image::getPath() {
    char path[256];
    return path;
}

std::string img::Image::getBlackImgPath() {
    // change black image file path to your own directory
    return R"(C:\Users\minht\CLionProjects\video_editor_BX23\src\image\default_images\black.jpg)";
}

// adds black areas to image
void img::Image::equalizeImgDim( double width, double height) {
    double fixedRatio = height / width;
    double imgRatio = this -> getRatio();

    // just resizing works
    if (imgRatio == fixedRatio) {
        this -> resizeImg( width, height );
        return;
    }

    std::cout<<imgRatio<<"  "<<fixedRatio<<std::endl;

    if (( imgRatio > fixedRatio ) ) {

        if ( this -> getModifiedHeight() > height ) {

            int new_width = std::floor( this -> getModifiedWidth() * height / this -> getModifiedHeight() );
            this ->resizeImg( new_width, height );

            // get the width of black image
            int black_width = floor( abs(width - new_width) / 2 );

            // create black image and resize it
            Image Black = img::Image(this -> getBlackImgPath());
            Black.resizeImg( black_width, height );

            //create collage vector
            std::vector<Image> arr = { Black, *this, Black };

            // set new image
            Collage newStichedImage = Collage(arr);
            newStichedImage.threeStitchInline( 0 );
            this ->setModifiedImg( newStichedImage.getModifiedImage() );

            return;

        } else if (this -> getModifiedHeight() < height) {

            int new_width = std::floor( this -> getModifiedWidth() * height / this -> getModifiedHeight() );
            this ->resizeImg( new_width, height );

            // get the width of black image
            int black_width = floor( abs(width - new_width) / 2 );

            // create black image and resize it
            Image Black = img::Image(this -> getBlackImgPath());
            Black.resizeImg( black_width, height );

            //create collage vector
            Image img_copy = Image(this->getModifiedImg());
            std::vector<Image> arr = { Black, img_copy, Black };

            // set new image
            Collage newStichedImage = Collage(arr);
            newStichedImage.threeStitchInline( 0 );
            this ->setModifiedImg( newStichedImage.getModifiedImage() );

            return;
        }

    }

    if (( imgRatio < fixedRatio ) ) {

        if ( this -> getModifiedWidth() > width ) {

            int new_height = std::floor( this -> getModifiedHeight() * width / this -> getModifiedWidth() );
            this -> resizeImg( width, new_height );

            // get the width of black image
            int black_height = floor( abs(height - new_height) / 2 );

            // create black image and resize it
            Image Black = img::Image(this -> getBlackImgPath());
            Black.resizeImg( width, black_height );

            //create collage vector
            std::vector<Image> arr = { Black, *this, Black };

            // set new image
            Collage newStichedImage = Collage(arr);
            newStichedImage.threeStitchInline( 1 );
            this ->setModifiedImg( newStichedImage.getModifiedImage() );

            return;

        } else if (this -> getModifiedWidth() < width) {

            int new_height = std::floor( this -> getModifiedHeight() * width / this -> getModifiedWidth() );
            this -> resizeImg( width, new_height );

            // get the width of black image
            int black_height = floor( abs(height - new_height) / 2 );

            // create black image and resize it
            Image Black = img::Image(this -> getBlackImgPath());
            Black.resizeImg( width, black_height );

            //create collage vector
            std::vector<Image> arr = { Black, *this, Black };

            // set new image
            Collage newStichedImage = Collage(arr);
            newStichedImage.threeStitchInline( 1 );
            this ->setModifiedImg( newStichedImage.getModifiedImage() );

            return;
        }
    }
}