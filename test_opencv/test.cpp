//
// Created by Vrushank on 11/12/2021.
//
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <unistd.h>

std::string get_curr_dir() {
    char add[256];
    getcwd(add, 256);

    // convert char to string
    std::string address;
    for (int i =0; i< strlen(add); i++)
        address += add[i];
    return address;
}

int main()
{
    std::string address = get_curr_dir();

    // if windows run this command
    std::string image_path = cv::samples::findFile(address + "\\..\\lena.jpg");
    // if mac run this command
//    std::string image_path = cv::samples::findFile(address + "/../lena.jpg");

    cv::Mat img = imread(image_path, cv::IMREAD_COLOR);
    if(img.empty()) {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    imshow("Display window", img);
    // Wait for a keystroke in the window
    int k = cv::waitKey(0);
    return 0;
}
