#include "collage.h"

using namespace img;
using namespace cv;


Mat hstitch(Mat mat1, Mat mat2){
    //later on we can add the division (currently)
    Mat output;
    int out_height = min(mat1.size().height, mat2.size().height); 
    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
    temp1.resize(mat1.size().width , out_height);
    temp2.resize(mat2.size().width, out_height);
    hconcat(mat1,mat2, output);
    return output;
}
img::Collage::Collage(int numImages, Image imageArr){
    this-> numImages = numImages;
    this-> imageArr = imageArr[numImages];
    double ratios[numImages];
    //calculate ratios
    double max_ratios;
    int max_ratios_index;
    for (i = 0; i < numImages; i++){
        ratios[i] = imageArr[i].getRatio();
        if (i == 0 || (ratios[i]> max_ratios)){
            max_ratios = ratios[i];
            max_ratios_index = i;
        }
    }
    this->ratios = ratios;
    this->max_ratios = max_ratios;
}
Mat vstitch(Mat mat1, Mat mat2){
    //later on we can add the division (currently)
    Mat output;
    int out_wdith = min(mat1.size().width, mat2.size().width); 
    //allocate temp1 and temp2 matrices to concatenate and then delete them later. so that we don't modify the original images.
    temp1.resize(out_wdith);
    temp2.resize(out_wdith, mat1.size().height);
    hconcat(mat1,mat2, mat2.size().height);
    return output;
}

void img::collage::twoStitch() {
    //stitch depending on sizes 

    if (numImages == 2) {
        //default stitching based on ratio
        //if both ratios h/w < 1 then it's better to do vertical stacking
        double minimum = min(ratios[0], ratios[1])
        double maximum = max(ratios[0], ratios[1])
        if (ratios[0] < 1 && ratios[1] < 1) {
            //width dominant
            this->getModifiedImg() = vstitch(imageArr[0].
            this->getMat(), imageArr[1].
            this->getMat());
        } else if (minimum < 1 && maximum > 1) {
            if (1 / minimum > maximum) {
                //the width to height ratio of one image is greater than the height to width ratio of the other
                //Thus width dominant so we vertical stitch
                this->getModifiedImg() = vstitch(imageArr[0].
                this->getMat(), imageArr[1].
                this->getMat());
            } else {
                this->getModifiedImg() = hstitch(imageArr[0].
                this->getMat(), imageArr[1].
                this->getMat());
            }
        } else {
            //height dominant
            this->getModifiedImg() = hstitch(imageArr[0].
            this->getMat(), imageArr[1].
            this->getMat());
        } //REMEMBER TO RESIZE AFTER!!
    } else{
        std::cout << "Must have only 2 images!" <<endl;
    }
}

