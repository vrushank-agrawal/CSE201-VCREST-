//
// Created by Vrushank on 11/12/2021.
//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    cout << "Video team is working :))" << endl;
    // whenever you are done with your opencv undo the comments below and test it
    /*
    std::string image_path = samples::findFile("copy the image path you want to show");
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if(k == 's')
    {
        imwrite("starry_night.png", img);
    }*/
    return 0;
}