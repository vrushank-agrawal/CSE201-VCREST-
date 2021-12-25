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
#include "../image/blurs.cpp"

#endif //OPENCV

using namespace cv;
using namespace std;
using namespace img;

#ifndef VIDEO_CLASS
#define VIDEO_CLASS

namespace vid {

    const int total_number_of_animations = 5;
    enum animation {
        Normal = 0, Rotation = 1, Zooming = 2, Cropping = 3
    };

    class Video {
    public:

        //Constructors

        //receives width, height and frames per second
        Video(int width, int height, int fps);

        Video(Image **images, double *start_times, double *times_of_display, int size, int width, int height, int fps);

        ~Video();

        void test();

        //Main working functions

        //adds Image pointer at specific time for some duration
        void Add(Image *img, double start_time, double time_to_display);

        //adds Image pointer in the end(normally user won't use this)
        void Insert(Image *img, double start_time, double time_to_display);

        //adds Image pointer at certain index (not meant to be used by user)
        void Insert(Image *img, double start_time, double time_to_display, int index);

        //Deletes everything associated to image pointer.
        void Delete(Image *img);

        //Applies animation (receives image pointer and animation type)
        void ApplyAnimation(Image *img, animation animation_type);

        //Removes from the vector at certain index(not meant to be used by user)
        void Remove(int index);

        //gets mat at certain time
        Mat GetMat(double time);

        //gets mat at certain frame
        Mat GetMatAtFrame(int frame_index);

        //gets image pointer from certain index
        Image *GetImgAtIndex(int index);

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
        struct ImageAnimator {
        public:
            ImageAnimator();

            ImageAnimator(Image *image, double start_time, double display_time, int fps);

            ImageAnimator(Image *image, double start_time, double display_time, int fps, animation animation_type);

            ~ImageAnimator();

            void Display();

            void Write(VideoWriter video_writer);

            void SetAnimation(animation animation_type);

            Mat GetMatAt(int frame_number);

            Mat NormalDisplay(int frame_number);

            Mat RotateAnimation(int frame_number);

            //Functions below should be of type Mat as well, not tested yet
            void ZoomAnimation(int frame_number);

            void CropAnimation();

            void InitFunctions();

            Mat Create_blank(int *color, int *size);

            Image *image;
            double time, start_time, fps;
            animation animation_type;

            Mat (ImageAnimator::*anim_functions[total_number_of_animations + 1 ])(int);
        };

    private:
        vector<Image *> image_pointers;
        vector<ImageAnimator> animators;
        Image blank;
        int number_of_animations;
        int width, height, fps;
    };

}


#endif // VIDEO_CLASS
