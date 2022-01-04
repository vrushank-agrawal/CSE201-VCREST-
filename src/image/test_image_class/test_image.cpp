//
// Created by Vrushank on 11/20/2021.
//

#include "../image.cpp"
#include "../blurs.cpp"
#include "../collage/collage.cpp"

#include <string>
#include <unistd.h>
#include <algorithm>

using img::Image;
using img::Collage;
//
//std::string get_curr_dir() {
//    char add[256];
//    getcwd(add, 256);
//
//    // convert char to string
//    std::string address;
//    for (int i =0; i< strlen(add); i++)
//        address += add[i];
//    return address;
//}

int main() {
    std::string add = get_curr_dir();
    // change path for macOS
    add += "\\..\\htest.jpg";

    std::string image_path = cv::samples::findFile(add, cv::IMREAD_COLOR);
    Image img1 = Image(image_path);

    std::string file = img1.getFilename();
    Mat matrix = img1.getMat();

// ------------------------BASIC FUNCTIONS---------------------------

//    img1.imgPreview("testing");
//    cout<<file<<endl;

//    img1.resizeImg(500, 600);
//    img1.imgModifiedPreview("testing_img_resize");

//    img1.rotateImg(25);
//    img1.imgModifiedPreview("testing_img_rotate");

    // test image dimension equalizing functions
//    img1.equalizeImgDim(1920, 1080);
//    img1.imgModifiedPreview("test image dimension equalizing");

//    img1.bilateralFilter(51 );
//    img1.imgModifiedPreview("testing_bilateral_filter");

    img1.addWeighted(0.1, 0.9);
    img1.imgModifiedPreview("testing_fade_function");


// ---------------------------BLUR PREVIEW----------------------------

    // testing dynamic image blur functions

    // equalize image first
//    img1.equalizeImgDim(1920, 1080);

//    img1.blurPreview(30 ,30 );
//    img1.imgBlurPreview("testing_blur_0");
//    img1.bilateralFilterPreview(31 );
//    img1.imgBilateralFilterPreview("testing_blur_0");
//    img1.boxBlurPreview(30 ,29 );
//    img1.imgBoxBlurPreview("testing_blur_0");
//    img1.gaussianBlurPreview(30 ,27 );
//    img1.imgGaussianBlurPreview("testing_blur_0");
//    img1.medianBlurPreview(31 );
//    img1.imgMedianBlurPreview("testing_blur_0");
//    img1.imgModifiedPreview("testing_blur_0");

//    int i = cv::waitKey(0);
//    img1.blurPreview(1 ,1 );
//    img1.imgBlurPreview("testing_blur_1");
//    img1.bilateralFilterPreview(1 );
//    img1.imgBilateralFilterPreview("testing_blur_1");
//    img1.boxBlurPreview(1 ,1 );
//    img1.imgBoxBlurPreview("testing_blur_1");
//    img1.gaussianBlurPreview(1 ,1 );
//    img1.imgGaussianBlurPreview("testing_blur_1");
//    img1.medianBlurPreview(1 );
//    img1.imgMedianBlurPreview("testing_blur_1");
//    img1.imgModifiedPreview("testing_blur_1");

//    int a = cv::waitKey(0);
//    img1.blurPreview(50 ,50 );
//    img1.imgBlurPreview("testing_blur_2");
//    img1.bilateralFilterPreview(51 );
//    img1.imgBilateralFilterPreview("testing_blur_2");
//    img1.boxBlurPreview(50 ,49 );
//    img1.imgBoxBlurPreview("testing_blur_2");
//    img1.gaussianBlurPreview(50 ,47 );
//    img1.imgGaussianBlurPreview("testing_blur_2");
//    img1.medianBlurPreview(51 );
//    img1.imgMedianBlurPreview("testing_blur_2");
//    img1.imgModifiedPreview("testing_blur_2");

//    int b = cv::waitKey(0);
//    img1.blurPreview(1 ,1 );
//    img1.imgBlurPreview("testing_blur_3");
//    img1.bilateralFilterPreview(1 );
//    img1.imgBilateralFilterPreview("testing_blur_3");
//    img1.boxBlurPreview(1 ,1 );
//    img1.imgBoxBlurPreview("testing_blur_3");
//    img1.gaussianBlurPreview(1 ,1 );
//    img1.imgGaussianBlurPreview("testing_blur_3");
//    img1.medianBlurPreview(1 );
//    img1.imgMedianBlurPreview("testing_blur_3");
//    img1.imgModifiedPreview("testing_blur_3");

//  -----------------------------BLURS-------------------------------

//    img1.blur(30 ,30 );
//    img1.imgModifiedPreview("testing_blur");

//    img1.gaussianBlur(4, 6);
//    img1.imgModifiedPreview("testing_gaussian_blur");

//    img1.medianBlur(5);
//    img1.imgModifiedPreview("testing_median_blur");

//    img1.boxBlur(5, 6);
//    img1.imgModifiedPreview("testing_box_filter");


// ----------------------------STITCHING------------------------------

    //define images and vectors

//    Image img2 = Image(image_path);
//    Image img3 = Image(image_path);
//    Image img4 = Image(image_path);
//    std::vector<Image> imageArr2 = {img1, img2};
//    std::vector<Image> imageArr3 = {img1, img2, img3};
//    std::vector<Image> imageArr4 = {img1, img2, img3, img4};

    //define collages
//    Collage collage2 = Collage(imageArr2);
//    Collage collage3 = Collage(imageArr3);
//    Collage collage4 = Collage(imageArr4);

    //run collage functions
//    collage2.twoStitch();
//    collage3.threeStitch();
//    collage4.fourStitch();
//    collage2.fourStitchRec(2);

    // display collage
//    Image collage_img2 = Image(collage2.getModifiedImage());
//    Image collage_img3 = Image(collage3.getModifiedImage());
//    Image collage_img4 = Image(collage4.getModifiedImage());

//    collage_img2.imgPreview("test_lena_collage2");
//    collage_img3.imgPreview("test_lena_collage3");
//    collage_img4.imgPreview("test_lena_collage4");


// --------------------------------EXIT--------------------------------

    int j = cv::waitKey(0);
    exit(0);
}