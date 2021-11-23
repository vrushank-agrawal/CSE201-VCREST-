//
// Created by Vrushank on 11/20/2021.
//

#include "../image.h"
#include "../image.cpp"
#include "../blurs.cpp"
//#include "../rotate_resize.cpp"
#include "../save.cpp"

using namespace cv;

int main()
{
    std::string image_path = samples::findFile("C:\\Users\\minht\\CLionProjects\\video_editor_BX23\\src\\testing_opencv\\lena.jpg");
    Image img1 = Image(image_path);

    string file = img1.getFilename();
    Mat matrix = img1.getMat();
    cout<<file<<endl;

    img1.imgPreview("testing");

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

//    img1.resizeImg(5, 6);
//    img1.imgModifiedPreview("testing_img_resize");
//    int p = waitKey(0);

    int j = waitKey(0);
}