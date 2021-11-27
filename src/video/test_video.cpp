#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "video.h"

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
    string imgpath = "..\\..\\video_samples\\A.png";
    Mat img1 = imread(imgpath);
    imgpath = "..\\..\\video_samples\\B.png";
    Mat img2 = imread(imgpath);
    Mat images[10];
    int times[10];
    images[0] = img1;
    images[1] = img2;
    times[0] = 100;
    times[1] = 100;
    vid::Video v(images, times, 2);
    v.test();
    v.DisplayCurrentVideo();
    v.Remove(0);
    v.DisplayCurrentVideo();

    cout << "Everything done, opencv works" << endl;
    return 0;
}