#pragma once

#ifndef OPENCV
#define OPENCV

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>

#endif //OPENCV

#include <iostream>

#ifndef IMAGE_CLASS
#define IMAGE_CLASS

namespace img {

    class Image {
        cv::Mat img_matrix;
        cv::Mat img_matrix_modified;
        std::string filename;

    public:
        Image();
        Image (cv::Mat mat);
        Image (const std::string &    filename);
        ~Image();

        // returns the Matrix associated to the image
        cv::Mat getMat();
        std::string getFilename();
        cv::Mat getModifiedImg();
        void setModifiedImg(cv::Mat mat);

        // returns current path of the directory
        std::string getPath();

        // returns path to black image
        std::string getBlackImgPath();

        // returns error if loaded image can't be read
        int return_img_error(int a);

        // returns true if input image is of valid format
        bool validImg(const std::string & 	filename);

        // returns a Matrix of the image color values
        cv::Mat decodeImg(const std::string & 	filename,
                      int 	            flags = cv::IMREAD_COLOR);

        //resets image dimensions by adding black areas
        void equalizeImgDim( int width, int height );

        //Returns ratio from dimensions:
        double getRatio();
        double getModifiedImageRatio();

        // return dimensions
        int getHeight();
        int getWidth();
        int getModifiedHeight();
        int getModifiedWidth();

        // Image matrix preview functions
        void imgPreview( const std::string & 	winname);
        void imgModifiedPreview( const std::string & winname);

        // Basic editing functions
        void resizeImg(int width, int height);
        void rotateImg(double angle);

        //Blurs
        void bilateralFilter(int distance);
        void blur(int width, int height);
        void boxBlur(int width, int height, int depth);
        void gaussianBlur(int width, int height);
        void medianBlur(int kernel_size);

    }; // Image() class

} //namespace

#endif // IMAGE_CLASS

#include "collage/collage.h"