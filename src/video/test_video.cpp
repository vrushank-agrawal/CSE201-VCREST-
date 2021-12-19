#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "video.h"
#include "video.cpp"
#include "../image/image.h"


using namespace std;
using namespace cv;

/*void read_video(){
    string video_name = "write your video name";
//example below
    video_name = "D:\\Dimitri\\Homeworks\\YEAR2\\CSE201_Project\\New folder\\video_editor_BX23\\src\\video\\Toilet_Paper.mp4";

    VideoCapture cap(video_name);

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream" << endl;
        return;
    }

    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.

    VideoWriter video("outcpp.avi", VideoWriter::fourcc('M','J','P','G'), 10, Size(frame_width, frame_height));
    while(1){
        Mat frame;
        cap >> frame;
        video.write(frame);
        imshow( "Frame", frame);
        char c = (char)waitKey(1);
        if( c == 27 )
            break;
    }
    cap.release();
    video.release();
}*/

int main(){
    Mat mat1, mat2, mat3;
    string imgpath = "..\\..\\video_samples\\A.png";
    mat1 = imread(imgpath);
    imgpath = "..\\..\\video_samples\\B.png";
    mat2 = imread(imgpath);
    imgpath = "..\\..\\video_samples\\C.jpg";
    mat3 = imread(imgpath);

    vid::Video v(mat1.size().width, mat1.size().height);
    v.test();
    v.Add(mat3, 50);
    v.Add(mat2, 50);
    v.Add(mat1, 50);
    v.Add(mat3, 50, 2);
    cout << v.AnimationNumber() << endl;
    v.DisplayCurrentVideo();

    v.Clear();
    cout << v.AnimationNumber() << endl;
    v.Add(mat2, 50);
    v.Resize(mat2.size().width, mat2.size().height);
    v.DisplayCurrentVideo();
    //v.WriteVideo("..//YESSS.mp4");
    //img1 = image_mat.getMat();
    //imshow( "Frame", img);

    cout << "We are here" << endl;
    //img2.rotateImg(30);
    //Mat img_fuck = img2.getModifiedImg();
    //img2.imgModifiedPreview("testing_img_rotate");
    //waitKey(0);
    cout << "Everything done, opencv works" << endl;
    return 0;
}