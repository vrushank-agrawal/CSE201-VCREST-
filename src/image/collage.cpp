#include "collage.h"
#include <algorithm>
#include <typeinfo>
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

img::Collage::Collage(vector<Image> inImageArr){
    this-> numImages = inImageArr.size();
    this-> imageArr = std::move(inImageArr);

    //calculate ratios
    ratios.clear();

    for (int i = 0; i < this-> numImages ; i ++ ){
        ratios.push_back(this->imageArr.at(i).getRatio());
        //find the dominant ratio of height to width
//        if (this -> maxRatios > 1) {
//            if (ratios[i] > this->maxRatios || ((ratios[i]<1) && (1 / ratios[i]) > this->maxRatios)) {
//                this->maxRatios = ratios[i];
//                this->maxRatiosIndex = i;
//            }
//        }
//        else if (this -> maxRatios <= 1) {
//            if (ratios[i] < this->maxRatios || ((ratios[i] > 1) && (1 / ratios[i]) < this->maxRatios)) {
//                this->maxRatios = ratios[i];
//                this->maxRatiosIndex = i;
//            }
//        }

    }

    // set image mat to NULL initially
    modifiedImage = NULL;
}
img::Collage::~Collage() {

}
void img::Collage::setModifiedImageArr(vector<Image> imageArrModified){
    this -> imageArrModified = imageArrModified;
}

int img::Collage::getNumImages(){
    return this -> numImages;
}

const std::vector<double>& img::Collage::getRatios(){
    return this -> ratios;
}


const std::vector<Image>& img::Collage::getImageArr(){
    return this -> imageArr;
}


void img::Collage::setModifiedImage(Mat modifiedMat) {
    this -> modifiedImage = modifiedMat;
}


Mat img::Collage::getModifiedImage() {
    return this -> modifiedImage;
}
vector<Image> img::Collage::getModiefiedImageArr(){
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
            this->setModifiedImage(vstitch(this->getImageArr().at(0),
                                           this->getImageArr().at(1)));
        } else if (minimum < 1 && maximum > 1) {
            if (1 / minimum > maximum) {
                //the width to height ratio of one image is greater than the height to width ratio of the other
                //Thus width dominant, so we do vertical stitch
                this->setModifiedImage(vstitch(this->getImageArr().at(0), this->getImageArr().at(1)));
            } else {
                this->setModifiedImage(hstitch(this->getImageArr().at(0), this->getImageArr().at(1)));
            }
        } else {

            //height dominant
            this->setModifiedImage(hstitch(this->getImageArr().at(0), this->getImageArr().at(0)));
        }  //REMEMBER TO RESIZE AFTER!!
    } else {
        std::cout << "A different amount of images than 2!";
    }
}
template <typename T>
int getMaxIndex(std::vector<T> arr){
    T max;
    int maxIndex = 0;
    if (arr.size()<1){
        return -1;
    }
    for(int i = 0; i< arr.size(); i++){
        if (i == 0){
            max = arr.at(i);
        }else if(arr.at(i)> max){
            max = arr.at(i);
            maxIndex = i;
        }
    }
    return maxIndex;
}
void img::Collage::threeStitch() {
    if (this->getNumImages() == 3) {
        //default stitching based on ratio
        //if both ratios h/w < 1 then it's better to do vertical stacking
        int maximum = getMaxIndex(this-> getRatios());
        std::cout << "maximum: " << typeid(maximum).name();
        vector<Image> subImageArr = this->getImageArr();
        vector<Image>::iterator maxIndex = subImageArr.begin() + maximum ;
        subImageArr.erase(maxIndex);
        Collage subCollage(subImageArr);
        subCollage.twoStitch();
        Image twoStitched(subCollage.getModifiedImage());



    } else{
        std::cout << "A different amount of images than 3!";
    }
}