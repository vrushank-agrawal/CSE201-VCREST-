#ifndef OPENCV
#define OPENCV

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>

#endif //OPENCV

using namespace cv;
using namespace std;

#ifndef IMAGE_CLASS
#define IMAGE_CLASS

namespace img {

    class Image {

        Mat img_matrix;
        Mat img_matrix_modified;
        string filename;
        string save_filename;

    public:
        
        Image(const string &    filename);

        ~Image();

        int return_img_error(int a);

        // returns the Matrix associated to the image
        Mat getMat();
        String getFilename();
        Mat getModifiedImg();
        void setModifiedImg(Mat mat);

        //counts number of images if a multi image file
        size_t countImg(const string & 	filename,
                        int 	        flags = IMREAD_ANYCOLOR);

        // returns true if input image is of valid format
        bool validImg(const string & 	filename);

        // returns a Matrix of the image color values
        Mat decodeImg(const String & 	filename,
                      int 	            flags = IMREAD_COLOR);

        // saves img in a certain file format
        bool saveImg(const String & 	filename,
                     InputArray 	img,
                     const std::vector< int > & 	params = std::vector< int >()
        );
        //Returns ratio from dimensions:
        double getRatio();
        
        // Image matrix preview functions
        void imgPreview( const String & 	winname);
        void imgModifiedPreview( const string & winname);

        // Basic editing functions in rotate_resize.cpp
        void resizeImg(int width, int height);
        void rotateImg(double angle);

        //Blurs in blurs.cpp
        void bilateralFilter(int distance);
        void blur(int width, int height);
        void boxBlur(int width, int height, int depth);
        void gaussianBlur(int width, int height);
        void medianBlur(int kernel_size);

    };
}


#endif // IMAGE_CLASS
