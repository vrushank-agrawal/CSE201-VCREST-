#ifndef OPENCV
#define OPENCV

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#endif //OPENCV

using namespace cv;
using namespace std;

#ifndef IMAGE_CLASS
#define IMAGE_CLASS

namespace img {

    class Image {

        Mat img_matrix;
        string filename;

    public:

        Image( string filename);

        ~Image();

        // returns the Matrix associated to the image
        Mat getMat();

        //counts number of images if a multi image file
        size_t countImg(const string & 	filename,
                        int 	        flags = IMREAD_ANYCOLOR);

        // returns true if input image is of valid format
        bool validImg(const string & 	filename);

        // returns a Matrix of the image color values
        Mat decodeImg(InputArray 	buf,
                      int 	        flags);

        // saves img in a certain file format
        bool saveImg();

        // Basic functions
        void resizeImg();
        void rotateImg();

        //Blurs
        void blur(int width, int height);
        void boxBlur(int width, int height, int ddepth);
        void gaussianBlur(int width, int height);
        void medianBlur(int width, int height);

    };
}


#endif // IMAGE_CLASS