#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main(){


    string video_name = "write your video name";
//example below
//    string video_name = "D:\\Dimitri\\Homeworks\\YEAR2\\CSE201_Project\\New folder\\video_editor_BX23\\src\\video\\Toilet_Paper.mp4";

    VideoCapture cap(video_name);

    // Check if camera opened successfully
    if(!cap.isOpened()){
        cout << "Error opening video stream" << endl;
        return -1;
    }

    // we will use this part later
    //string imgpath = "write image name";
    //Mat img = imread(imgpath);
    int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);;
    int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);

    // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
    VideoWriter video("outcpp.avi", VideoWriter::fourcc('M','J','P','G'), 10, Size(frame_width,frame_height));
    while(1){

        Mat frame;

        cap >> frame;
        if (frame.empty())
            break;
        video.write(frame);

        imshow( "Frame", frame);

        char c = (char)waitKey(1);
        if( c == 27 )
            break;
    }
    cap.release();
    video.release();

    destroyAllWindows();

    // in the end the avi file must be created and you must see the video
    cout << "Everything done, opencv works" << endl;
    return 0;
}