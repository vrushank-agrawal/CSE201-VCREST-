#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "video.h"
#include "video.cpp"

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

    Image img1, img2, img3, img4, img5;
    img1 = Image(mat1);
    img2 = Image(mat2);
    img3 = Image(mat3);
    img4 = Image(mat3);
    img5 = Image(mat3);

    //imshow("Frame", img1.getModifiedImg());
    //waitKey(2000);
    Video v(1000, 500, 30);
    v.Add(&img1, 2.5, 2.5);
    v.Add(&img4, 5.1, 3);
    v.Add(&img2, 8.1, 3);
    v.Add(&img3, 12, 2);
    cout << v.AnimationNumber() << endl;
    v.WriteVideo("..//Before.mp4");


    //v.Delete(&img4);
    v.ApplyAnimation(&img1, Rotation);
    v.ApplyAnimation(&img3, Rotation);
    cout << v.AnimationNumber() << endl;
    v.WriteVideo("..//YESSS.mp4");

    /*for (int i = 60; i < 310; i++) {
        Mat toshow = v.GetMatAtFrame(i);
        imshow("Frame", toshow);
        waitKey(5);
    }

    img5.equalizeImgDim(1000, 600);
    Mat toshow = img5.getModifiedImg();
    imshow("Frame", toshow);
    waitKey(3000);*/

    cout << "Everything done, opencv works" << endl;
    return 0;
}