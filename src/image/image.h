#ifndef IMAGE_CLASS
#define IMAGE_CLASS

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>

#include <iostream>
#include <cstdlib>


namespace img {

    class Image {
        cv::Mat img_matrix;
        cv::Mat img_matrix_modified;
        cv::Mat img_matrix_blur;
        cv::Mat img_matrix_bilateralFilter;
        cv::Mat img_matrix_boxBlur;
        cv::Mat img_matrix_gaussianBlur;
        cv::Mat img_matrix_medianBlur;
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
        cv::Mat getBlurImg();
        cv::Mat getBilateralFilterImg();
        cv::Mat getBoxBlurImg();
        cv::Mat getGaussianBlurImg();
        cv::Mat getMedianBlurImg();

        // sets the matrix associated to the image
        void setModifiedImg(cv::Mat mat);
        void setOriginalImg(cv::Mat mat);
        void setBlurImg(cv::Mat mat);
        void setBilateralFilterImg(cv::Mat mat);
        void setBoxBlurImg(cv::Mat mat);
        void setGaussianBlurImg(cv::Mat mat);
        void setMedianBlurImg(cv::Mat mat);

        // returns error if loaded image can't be read
        int return_img_error(int a);
        // returns true if input image is of valid format
        bool validImg(const std::string & 	filename);
        // returns a Matrix of the image color values
        cv::Mat decodeImg(const std::string & 	filename, int flags = cv::IMREAD_COLOR);

        //resets image dimensions by adding black areas
        void equalizeImgDim( double width, double height );
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
        void blurPreview(int width, int height);
        void blur(int width, int height);
        void boxBlurPreview(int width, int height, int depth);
        void boxBlur(int width, int height, int depth);
        void gaussianBlurPreview(int width, int height);
        void gaussianBlur(int width, int height);
        void medianBlurPreview(int kernel_size);
        void medianBlur(int kernel_size);

    }; // Image() class

    const cv::Mat blackMat = cv::Mat(1920, 1080, CV_8UC3, cv::Scalar(0, 0, 0));
} //namespace

#endif // IMAGE_CLASS

#include "collage/collage.h"