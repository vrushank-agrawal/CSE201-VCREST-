#ifndef IMAGE_CLASS
#define IMAGE_CLASS

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>

#include <iostream>
#include <cstdlib>



namespace img {

    enum BlurType {
        Normal, Gaussian, Median
    };

    class Image {
        cv::Mat img_matrix;
        cv::Mat img_matrix_modified;
        cv::Mat img_matrix_bilateralFilter;
        cv::Mat current_unblur_matrix;
        std::string filename;

    public:
        // constructors
        Image();
        Image (cv::Mat mat);
        Image (const std::string &    filename);
        ~Image();

        // returns the Matrix associated to the image
        cv::Mat getMat();
        std::string getFilename();
        cv::Mat getModifiedImg();

        // sets the matrix associated to the image
        cv::Mat getCurrentUnblurImg();
        void setModifiedImg(cv::Mat mat);
        void setCurrentUnblurImg(cv::Mat mat);
        void setOriginalImg(cv::Mat mat);
        void setBlurImg(cv::Mat mat);
        void setBilateralFilterImg(cv::Mat mat);

        // returns error if loaded image can't be read
        int return_img_error(int a);
        // returns true if input image is of valid format
        bool validImg(const std::string & 	filename);
        // returns a Matrix of the image color values
        cv::Mat decodeImg(const std::string & 	filename, int flags = cv::IMREAD_COLOR);

        //resets image dimensions by adding black areas
        void equalizeImgDim(double width, double height);
        void sendToStitch(int val, Image * img);
        void hcon (Image * img );
        void vcon (Image * img );

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
        void imgBlurPreview( const std::string & winname);
        void imgBilateralFilterPreview( const std::string & winname);
        void imgBoxBlurPreview( const std::string & winname);
        void imgGaussianBlurPreview( const std::string & winname);
        void imgMedianBlurPreview( const std::string & winname);

        // Basic editing functions
        void resizeImg(int width, int height);
        void rotateImg(double angle);
        void rotateImgFit(double angle);

        //Blurs and their previews
        void bilateralFilterPreview(int distance);
        void bilateralFilter(int distance);
        void blur(int width, int height);
        void boxBlur(int width, int height, int depth = -1);
        void gaussianBlur(int width, int height);
        void medianBlur(int kernel_size);
        
        // functions needed for the fade in animation
        void addWeighted( double alpha, double beta, double gamma);


    }; // Image() class

    const cv::Mat blackMat = cv::Mat(1280, 720, CV_8UC3, cv::Scalar(0, 0, 0));
} //namespace

#endif // IMAGE_CLASS

#include "collage/collage.h"
