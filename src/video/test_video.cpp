#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "video.h"
#include "video.cpp"

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

using namespace std;

int main(){

    cv::Mat mat1, mat2, mat3;
    std::string imgpath = "D:\\Dimitri\\Homeworks\\YEAR2\\CSE201_Project\\Video_part\\video_editor_BX23\\src\\video_samples\\A.png";
    mat1 = cv::imread(imgpath);
    imgpath = "D:\\Dimitri\\Homeworks\\YEAR2\\CSE201_Project\\Video_part\\video_editor_BX23\\src\\video_samples\\B.png";
    mat2 = cv::imread(imgpath);
    imgpath = "D:\\Dimitri\\Homeworks\\YEAR2\\CSE201_Project\\Video_part\\video_editor_BX23\\src\\video_samples\\C.jpg";
    mat3 = cv::imread(imgpath);

    img::Image img1, img2, img3, img4, img5, img6;
    img1 = img::Image(mat1);
    img2 = img::Image(mat2);
    img3 = img::Image(mat3);
    img4 = img::Image(mat3);
    img5 = img::Image(mat3);
    img6 = img::Image(mat3);

    vid::Video v(1000, 500, 30);
    v.addImage(&img1, 2.5, 2.5);
    v.addImage(&img4, 5.1, 3);
    v.addImage(&img2, 8.1, 3);
    v.addImage(&img3, 12, 2);
    std::cout << v.animationNumber() << std::endl;
    //int codec = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    //v.writeVideo("..//Before.mp4", codec);

    cout << "****************" << endl;


    v.applyAnimation(&img4, vid::FadeIn);
    v.applyAnimation(&img1, vid::Rotation);
    v.applyAnimation(&img3, vid::Rotation);
    v.applyAnimation(&img2, vid::ZoomIn);
    v.applyAnimation(&img3, vid::ZoomOut);
    std::cout << v.animationNumber() << std::endl;

    v.writeVideo("..//YESSS.mp4", (int)cv::VideoWriter::fourcc('m', 'p', '4', 'v'));
    //cv::imshow( "Frame", img5.getModifiedImg());
    //cv::waitKey(2000);
    //img5.addWeighted(0.7, 0.3);
    //img5.addWeighted(0.3, 0.7);
    //cv::imshow( "Frame", img5.getModifiedImg());
    //cv::waitKey(2000);

    std::cout << "Everything done, opencv works" << std::endl;
    return 0;
}