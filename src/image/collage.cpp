#include "collage.h"

using namespace img;
using namespace cv;


Mat hstitch(Image img1, Image img2) {
    //later on we can add the division (currently)
    Mat output;
    int out_height = min(img1.getMat().size().height, img2.getMat().size().height);
    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
    Image temp1(img1.getMat()), temp2(img2.getMat());
    temp1.resizeImg(img1.getMat().size().width ,out_height);
    temp2.resizeImg(img2.getMat().size().width, out_height);
    hconcat(img1.getMat(),img2.getMat(), output);
    return output;
}
Mat vstitch(Image img1, Image img2){
    //later on we can add the division (currently)
    Mat output;
    int out_width = min(img1.getMat().size().width, img2.getMat().size().width);

    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
    Image temp1(img1.getMat()), temp2(img2.getMat());
    temp1.resizeImg(out_width, img1.getMat().size().height);
    temp2.resizeImg(out_width, img2.getMat().size().height);
    vconcat(img1.getMat(),img2.getMat(),output);
    return output;
}

img::Collage::Collage(int inNumImages, vector<Image> inImageArr){
    this-> numImages = inNumImages;
    this-> imageArr = std::move(inImageArr);

    //calculate ratios
    ratios.clear();

    for (int i = 0; i < this-> numImages ; i ++ ){
        ratios.push_back(this->imageArr.at(i).getRatio());
        //find the dominant ratio of height to width
        if (this -> maxRatios > 1) {
            if (ratios[i] > this->maxRatios || ((ratios[i]<1) && (1 / ratios[i]) > this->maxRatios)) {
                this->maxRatios = ratios[i];
                this->maxRatiosIndex = i;
            }
        }
        else if (this -> maxRatios <= 1) {
            if (ratios[i] < this->maxRatios || ((ratios[i] > 1) && (1 / ratios[i]) < this->maxRatios)) {
                this->maxRatios = ratios[i];
                this->maxRatiosIndex = i;
            }
        }

    }

    // set image mat to NULL initially
    modifiedImage = NULL;
}
img::Collage::~Collage() {

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



Mat img::Collage::getModifiedImage() {
    return this -> modifiedImage;
}

void img::Collage::twoStitch() {
    //stitch depending on sizes 

    if (this->getNumImages() == 2) {
        //default stitching based on ratio
        //if both ratios h/w < 1 then it's better to do vertical stacking
        double minimum = min(this->getRatios().at(0), this->getRatios().at(1));
        double maximum = max(this->getRatios().at(0), this->getRatios().at(1));
        if (this->getRatios().at(0) < 1 && this->getRatios().at(1) < 1) {
            //width dominant
            this->getModifiedImage() = vstitch(this->getImageArr().at(0),
                                               this->getImageArr().at(1));
        } else if (minimum < 1 && maximum > 1) {
            if (1 / minimum > maximum) {
                //the width to height ratio of one image is greater than the height to width ratio of the other
                //Thus width dominant, so we do vertical stitch
                this->getModifiedImage() = vstitch(this->getImageArr().at(0), this->getImageArr().at(1));
            } else {
                this->getModifiedImage() = hstitch(this->getImageArr().at(0), this->getImageArr().at(1));
            }
        } else {

            //height dominant
            this->getModifiedImage() = hstitch(this->getImageArr().at(0), this->getImageArr().at(0));
        }  //REMEMBER TO RESIZE AFTER!!
    }
}

