#ifndef OPENCV
#define OPENCV

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#endif //OPENCV

using namespace cv;
using namespace std;

#ifndef VIDEO_CLASS
#define VIDEO_CLASS

namespace vid {

    class Video {
    public:
        Video();
        Video(Mat image, int time_of_display);
        Video(Mat *images, int *times_of_display, int size);
        ~Video();
        void test();
        void CreateVideo(string output_name);
        void DisplayCurrentVideo();
        void Add(Mat img, int time_to_display);
        void Remove(int index);
        void ApplyAnimation(int index);
        void Clear();
        struct ImageAnimator{
        public:
            ImageAnimator(Mat img, int display_time);
            ~ImageAnimator(){};
            void ZoomAnimation(double ratio);
            //void RotateAnimation();
            void Display();

        private:
            Mat img;
            int time, animation_type;
        };
    private:
        vector<Mat> images;
        vector<ImageAnimator> animators;
        int number_of_animations;
    };

}


#endif // VIDEO_CLASS
