#include "collage.h"
#include <algorithm>

using cv::Mat;
using std::vector;
using img::Image;

cv::Mat hstitch(Image img1, Image img2) {

    //later on we can add the division (currently)
    cv::Mat output;
    int out_height = std::min(img1.getMat().size().height, img2.getMat().size().height);

    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
    Image temp1(img1.getMat()), temp2(img2.getMat());
    temp1.resizeImg(img1.getMat().size().width ,out_height);
    temp2.resizeImg(img2.getMat().size().width, out_height);
    hconcat(temp1.getModifiedImg(),temp2.getModifiedImg(), output);

    return output;
}


cv::Mat vstitch(Image img1, Image img2){

    //later on we can add the division (currently)
    cv::Mat output;
    int out_width = std::min(img1.getMat().size().width, img2.getMat().size().width);

    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
    Image temp1(img1.getMat()), temp2(img2.getMat());
    temp1.resizeImg(out_width, img1.getMat().size().height);
    temp2.resizeImg(out_width, img2.getMat().size().height);
    vconcat(temp1.getModifiedImg(),temp2.getModifiedImg(),output);

    return output;
}

img::Collage::Collage(vector<Image> inImageArr){
    this-> numImages = inImageArr.size();
    this-> imageArr = std::move(inImageArr);

    //calculate ratios
    ratios.clear();

    for (int i = 0; i < this-> numImages ; i ++ ){
        ratios.push_back(this->imageArr.at(i).getRatio());
    }

    // set image mat to NULL initially
    modifiedImage = cv::Mat() ;
}

img::Collage::~Collage() {}

void img::Collage::setModifiedImageArr(vector<Image> imageArrModified){
    this -> imageArrModified = imageArrModified;
    this -> modifiedNumImages = imageArrModified.size();
    modifiedRatios.clear();
    for (int i = 0; i < this-> modifiedNumImages ; i ++ ){
        modifiedRatios.push_back(this->imageArrModified.at(i).getRatio());
    }
}

int img::Collage::getNumImages(){
    return this -> numImages;
}

const std::vector<double>& img::Collage::getRatios(){
    return this -> ratios;
}

const std::vector<double>& img::Collage::getModifiedRatios(){
    return this -> modifiedRatios;
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

void img::Collage::imgModifiedPreview(const std::string &window) {
    cv::Mat mat = this -> getModifiedImage();
    imshow(window, mat);
}

vector<Image> img::Collage::getModifiedImageArr(){
    return this -> imageArrModified;
}


void img::Collage::twoStitch(bool original= true ) {
    //stitch depending on sizes
    vector<Image> arr;
    if (original){
        arr = this->getImageArr();
    }else{
        arr = this->getModifiedImageArr();
    }
    if (arr.size() == 2) {

        //default stitching based on ratio
        //if both ratios h/w < 1 then it's better to do vertical stacking
        double minimum = cv::min(arr.at(0).getRatio(), arr.at(1).getRatio());
        double maximum = cv::max(arr.at(0).getRatio(), arr.at(1).getRatio());
        if (arr.at(0).getRatio() < 1 && arr.at(1).getRatio() < 1) {
            //width dominant
            this->setModifiedImage(vstitch(arr.at(0), arr.at(1)));
        } else if (minimum < 1 && maximum >= 1) {
            if (1 / minimum >= maximum) {
                //the width to height ratio of one image is greater than the height to width ratio of the other
                //Thus width dominant, so we do vertical stitch
                this->setModifiedImage(vstitch(arr.at(0), arr.at(1)));
            } else {
                this->setModifiedImage(hstitch(arr.at(0), arr.at(1)));
            }
        } else {
            //height dominant
            this->setModifiedImage(hstitch(arr.at(0), arr.at(1)));
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

// slow method for inline stitching (not used anymore)
void img::Collage::threeStitchInline(int val) {

    if (this->getNumImages() == 3) {
        // val = 0 = horizontal
        if (val == 0 ) {
            cv::Mat output;

            Image img1 = this -> getImageArr()[0];
            Image img2 = this -> getImageArr()[1];
            Image img3 = this -> getImageArr()[2];

            cv::hconcat(img1.getModifiedImg(), img2.getModifiedImg(), output);
            cv::hconcat(output, img3.getModifiedImg(), output);

            this ->setModifiedImage(output);
        }
        // val = 1 = vertical
        else if (val == 1) {
            cv::Mat output;

            Image img1 = this -> getImageArr()[0];
            Image img2 = this -> getImageArr()[1];
            Image img3 = this -> getImageArr()[2];

            cv::vconcat(img1.getModifiedImg(), img2.getModifiedImg(), output);
            cv::vconcat(output, img3.getModifiedImg(), output);

            this ->setModifiedImage(output);
        }
    } else{
        std::cout << "A different amount of images than 3!";
    }
}

void img::Collage::threeStitch() {
    if (this->getNumImages() == 3) {
        //default stitching based on ratio
        //if both ratios h/w < 1 then it's better to do vertical stacking
        int maximum = getMaxIndex(this-> getRatios());
        // std::cout << "maximum: " << typeid(maximum).name();
        vector<Image> subImageArr = this->getImageArr();
        auto maxIndex = subImageArr.begin() + maximum ;
        subImageArr.erase(maxIndex);
        Collage subCollage(subImageArr);
        subCollage.twoStitch();
        Image twoStitched(subCollage.getModifiedImage());
        vector<Image> modifiedImageArr;
        modifiedImageArr.push_back(twoStitched);
        modifiedImageArr.push_back(*maxIndex);

        this -> setModifiedImageArr(modifiedImageArr);
        this -> twoStitch(false);

    } else{
        std::cout << "A different amount of images than 3!";
    }
}


void img::Collage::fourStitch(bool original= true) {
    if (this->getNumImages() == 4) {
        vector<double> ratios_vector;
        vector<Image> subImageArr1;
        if (original){
            ratios_vector = this-> getRatios();
            subImageArr1 = this->getImageArr();
        } else{
            ratios_vector = this-> getModifiedRatios();
            subImageArr1 = this->getModifiedImageArr();
        }

        int maximum = getMaxIndex(ratios_vector);
        // std::cout << "maximum: " << typeid(maximum).name();

        vector<Image> subImageArr2;
        //split into two collages of double stitch and then stitch all of them together
        vector<Image>::iterator maxIndex = subImageArr1.begin() + maximum ;
        vector<double>::iterator maxRatiosIndex = ratios_vector.begin() + maximum ;
        subImageArr2.push_back(*maxIndex);
        ratios_vector.erase(maxRatiosIndex);
        subImageArr1.erase(maxIndex);
        int secondMaximum = getMaxIndex(ratios_vector);
        vector<Image>::iterator secondMaxIndex = subImageArr1.begin() + secondMaximum ;
        subImageArr1.erase(secondMaxIndex);
        subImageArr2.push_back(*secondMaxIndex);
        Collage subCollage1(subImageArr1);
        Collage subCollage2(subImageArr2);
        subCollage1.twoStitch();
        subCollage2.twoStitch();
        vector<Image> imageArrModified ={subCollage1.getModifiedImage(), subCollage2.getModifiedImage()};
        this->setModifiedImageArr(imageArrModified);
        this->twoStitch(false);

    } else{
        std::cout << "A different amount of images than 4!";
    }
}

void img::Collage::fourStitchRecAux(bool original = false, int times= 0){
    if (times > 0) {
        this->fourStitch(original);
        Image img1(this->getModifiedImage());
        Image img2(this->getModifiedImage());
        Image img3(this->getModifiedImage());
        Image img4(this->getModifiedImage());
        this->setModifiedImageArr({img1, img2, img3, img4});
        times--;
        fourStitchRecAux(original = false, times);
    }
}

void img::Collage::fourStitchRec(int times){
    fourStitchRecAux(true, times);
}
