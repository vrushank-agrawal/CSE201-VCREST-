#ifndef OPENCV
#define OPENCV

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../image/image.cpp"
#endif //OPENCV

using namespace cv;
using namespace std;
using namespace img;

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
        void Add(Mat image_mat, int time_to_display);
        void Add(Mat image_mat, int time_to_display, int index);
        void Remove(int index);
        void ApplyAnimation(int index);
        void Resize(int width, int height);
        int AnimationNumber();
        void Clear();

        //Animator structure which is capable of displaying
        //current image for that time and applying the animation
        struct ImageAnimator{
        public:
            ImageAnimator(Image image, int display_time);
            ~ImageAnimator();
            void ZoomAnimationDisplay();
            void ZoomAnimationWrite(VideoWriter video_writer);
            void RotateAnimation();
            void CropAnimation();
            void CollageAnimation();
            Mat Create_blank(int* color, int* size);
            void Display();
            void Write(VideoWriter video_writer);

            Image image;
            int time, animation_type;
        };

    private:
        vector<Mat> image_mats;
        vector<ImageAnimator> animators;
        int number_of_animations;
        int width, height;
    };

}


#endif // VIDEO_CLASS
