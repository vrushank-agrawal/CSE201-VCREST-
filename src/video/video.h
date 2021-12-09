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

        //Constructors
        Video(int width, int height);
        Video(Mat *images, int *times_of_display, int size, int width, int height);
        ~Video();

        //Main working functions
        void test();
        void WriteVideo(string output_name);
        void DisplayCurrentVideo();
        void Add(Mat img, int time_to_display);
        void Add(Mat img, int time_to_display, int index);
        void Remove(int index);
        void ApplyAnimation(int index);
        void Resize(int width, int height);
        int AnimationNumber();
        void Clear();

        //Animator structure which is capable of displaying
        //current image for that time and applying the animation
        struct ImageAnimator{
        public:
            ImageAnimator(Mat img, int display_time);
            ~ImageAnimator();
            void ZoomAnimationDisplay(double ratio);
            void ZoomAnimationWrite(VideoWriter video_writer);
            void RotateAnimation(double angle);
            void FlyAnimation(Mat background);
            Mat get_mat() {
                return this -> img;
            }
            void Display();
            void Write(VideoWriter video_writer);

            Mat img;
            int time, animation_type;
        };

    private:
        vector<Mat> images;
        vector<ImageAnimator> animators;
        int number_of_animations;
        int width, height;
    };

}


#endif // VIDEO_CLASS
