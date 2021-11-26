#include "collage.h"

using namespace img;
using namespace cv;


Mat hstitch(Mat mat1, Mat mat2) {
    //later on we can add the division (currently)
    Mat output;
    int out_height = min(mat1.size().height, mat2.size().height); 
    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
    Image temp1(mat1), temp2(mat2);

    temp1.resizeImg(mat1.size().width , out_height);
    temp2.resizeImg(mat2.size().width, out_height);
    hconcat(mat1,mat2, output);
    return output;
}

img::Collage::Collage(int numImages, vector<Image> imageArr){
    this-> numImages = numImages;
    this-> imageArr = std::move(imageArr);

    //calculate ratios
    maxRatios = 0;
    ratios.clear();
    maxRatiosIndex = 0;
    for (int i = 0; i < imageArr.size() ; i ++ ){
        ratios.push_back(imageArr[i].getRatio());
        if (i == 0 || (ratios[i] > maxRatios)){
            maxRatios = ratios[i];
            maxRatiosIndex = i;
        }
    }

    // set image mat to NULL initially
    modifiedImage = NULL;
}

int img::Collage::getNumImages(){
    return this -> numImages;
}

const std::vector<double>& img::Collage::getRatios(){
    return this -> ratios;
}

double img::Collage::getMaxRatios(){
    return this -> maxRatios;
}

const std::vector<Image>& img::Collage::getImageArr(){
    return this -> imageArr;
}

int img::Collage::getMaxRatiosIndex(){
    return this -> maxRatiosIndex;
}

Mat vstitch(Mat mat1, Mat mat2){
    //later on we can add the division (currently)
    Mat output;
    int out_width = min(mat1.size().width, mat2.size().width);

    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.

    Image temp1(mat1), temp2(mat2);

    temp1.resizeImg(out_width, mat1.size().height);
    temp2.resizeImg(out_width, mat2.size().height);
    hconcat(mat1,mat2, mat2.size().height);
    return output;
}

Mat img::Collage::getModifiedImage() {
    return this -> modifiedImage;
}

void img::Collage::twoStitch() {
    //stitch depending on sizes 

    if (this->getNumImages() == 2) {
        //default stitching based on ratio
        //if both ratios h/w < 1 then it's better to do vertical stacking
        double minimum = min(this -> getRatios[0], this -> getRatios[1]);
        double maximum = max(this -> getRatios[0], this -> getRatios[1]);
        if (this -> getRatios[0] < 1 && this -> getRatios[1] < 1) {
            //width dominant
            this -> getModifiedImage() = vstitch(this -> getImageArr()[0].getMat(),
                                                 this -> getImageArr()[1].getMat());
        } else if (minimum < 1 && maximum > 1) {
            if (1 / minimum > maximum) {
                //the width to height ratio of one image is greater than the height to width ratio of the other
                //Thus width dominant, so we do vertical stitch
                this -> getModifiedImage() = vstitch(this->getImageArr()[0].this->getMat(), this->getImageArr()[1].this->getMat());
            } else {
                this -> getModifiedImage() = hstitch(this->getImageArr()[0].this->getMat(), this->getImageArr()[1].this->getMat());
            }
        } else {

            //height dominant
            this -> getModifiedImage() = hstitch(this -> getImageArr()[0].getMat(), this -> getImageArr()[1].getMat());
        } //REMEMBER TO RESIZE AFTER!!
    } else{
        std::cout << "must have 2 images only" <<endl;
    }
}

