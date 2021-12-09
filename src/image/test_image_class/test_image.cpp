//
// Created by Vrushank on 11/20/2021.
//

//#include "../image.h"
#include "../image.cpp"
#include "../blurs.cpp"
#include "../rotate_resize.cpp"
//#include "../save.cpp"
#include "../collage/collage.cpp"

using namespace cv;

int main(){
    std::string image_path = samples::findFile("lena.jpg");
    Image img1 = Image(image_path);
    Image img2 = Image(image_path);
    Image img3 = Image(image_path);
    Image img4 = Image(image_path);

    string file = img1.getFilename();
    Mat matrix = img1.getMat();
//    cout<<file<<endl;

//    img1.imgPreview("testing");

//    img1.bilateralFilter(51 );
//    img1.imgModifiedPreview("testing_bilateral_filter");
//    int k = waitKey(0);

//    img1.blur(5 ,6 );
//    img1.imgModifiedPreview("testing_blur");
//    int l = waitKey(0);

//    img1.gaussianBlur(4, 6);
//    img1.imgModifiedPreview("testing_gaussian_blur");
//    int m = waitKey(0);

//    img1.medianBlur(5);
//    img1.imgModifiedPreview("testing_median_blur");
//    int n = waitKey(0);

//    img1.boxBlur(5, 6);
//    img1.imgModifiedPreview("testing_box_filter");
//    int o = waitKey(0);

//    img1.resizeImg(500, 600);
//    img1.imgModifiedPreview("testing_img_resize");
//    int p = waitKey(0);

//    img1.rotateImg(25);
//    img1.imgModifiedPreview("testing_img_rotate");
//    int q = waitKey(0);


    // test stitching functions

    //define vectors
    vector<Image> imageArr2 = {img1, img2};
    vector<Image> imageArr3 = {img1, img2, img3};
    vector<Image> imageArr4 = {img1, img2, img3, img4};

    //define collages
    Collage collage2 = Collage(imageArr2);
    Collage collage3 = Collage(imageArr3);
    Collage collage4 = Collage(imageArr4);

    //run collage functions
    collage2.twoStitch();
    collage3.threeStitch();
    collage4.fourStitch();
//    collage2.fourStitchRec(2);

    // display collage
    Image collage_img2 = Image(collage2.getModifiedImage());
    Image collage_img3 = Image(collage3.getModifiedImage());
    Image collage_img4 = Image(collage4.getModifiedImage());

    collage_img2.imgPreview("test_lena_collage2");
    collage_img3.imgPreview("test_lena_collage3");
    collage_img4.imgPreview("test_lena_collage4");
    int r = waitKey(0);

    int j = waitKey(0);
}