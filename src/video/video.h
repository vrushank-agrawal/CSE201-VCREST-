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

    const int total_number_of_animations = 5;
    enum animation {Normal=0, Rotation=1, Zooming=2, Cropping=3};

    class Video {
    public:

        //Constructors
        Video(int width, int height, int fps);
        Video(Image **images, double *start_times, double *times_of_display, int size, int width, int height, int fps);
        ~Video();
        void test();

        //Main working functions
        void Add(Image *img, double start_time, double time_to_display);
        void Insert(Image *img, double start_time, double time_to_display);
        void Insert(Image *img, double start_time, double time_to_display, int index);
        void Delete(Image *img);
        void ApplyAnimation(Image *img, animation animation_type);
        void Remove(int index);
        Mat GetMat(double time);
        Mat GetMat(int frame_index);

        void WriteVideo(string output_name);

        //User doesn't need these functions
        void DisplayCurrentVideo();
        int GetPlace(double time);
        int GetIndex(Image *img);
        void Resize(int width, int height);
        void AddBlank(VideoWriter video_writer, double time);
        void ShowBlank(double time);
        int AnimationNumber();
        void Clear();

        //Animator structure which is capable of displaying
        //current image for that time and applying the animation
        struct ImageAnimator{
        public:
            ImageAnimator();
            ImageAnimator(Image *image, double start_time, double display_time, int fps);
            ImageAnimator(Image *image, double start_time, double display_time, int fps, animation animation_type);
            ~ImageAnimator();

            void Display();
            void Write(VideoWriter video_writer);
            void SetAnimation(animation animation_type);

            Mat NormalDisplay(int frame_number);
            Mat RotateAnimation(int frame_number);
            //Functions below should be of type Mat as well, not tested yet
            void ZoomAnimation();
            void CropAnimation();

            void InitFunctions();
            Mat Create_blank(int* color, int* size);

            Image *image;
            double time, start_time, fps;
            animation animation_type;
            Mat (ImageAnimator::*anim_functions[total_number_of_animations+1])(int);
        };

    private:
        vector< Image* > image_pointers;
        vector<ImageAnimator> animators;
        Image blank;
        int number_of_animations;
        int width, height, fps;
    };

}


#endif // VIDEO_CLASS
