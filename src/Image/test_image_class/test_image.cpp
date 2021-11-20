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

//    img1.imgPreview("testing");
//    int k = waitKey(0);

//    img1.blur(5 ,6 );
//    img1.imgModifiedPreview("testing_blur");
//    int k = waitKey(0);

//    img1.gaussianBlur(4, 5);
//    img1.imgModifiedPreview("testing_gaussianblur");
//    int k = waitKey(0);

//    img1.medianBlur(5);
//    img1.imgPreview("testing_median_blur");
//    int k = waitKey(0);

}