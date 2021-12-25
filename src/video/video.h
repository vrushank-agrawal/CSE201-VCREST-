#ifndef VIDEO_CLASS
#define VIDEO_CLASS

#ifndef OPENCV
#define OPENCV

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#endif //OPENCV

#include <iostream>
#include <vector>
#include <string>
#include "image.h"

using namespace cv;
using namespace std;
using namespace img;

namespace vid {

    const int total_number_of_animations = 5;
    enum Animation {
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
        void addImage(Image *img, double start_time, double time_to_display);

        //adds Image pointer in the end(normally user won't use this)
        void insertImage(Image *img, double start_time, double time_to_display);

        //adds Image pointer at certain index (not meant to be used by user)
        void insertImage(Image *img, double start_time, double time_to_display, int index);

        //Deletes everything associated to image pointer.
        void deleteImage(Image *img);

        //Applies Animation (receives image pointer and Animation type)
        void applyAnimation(Image *img, Animation animation_type);

        //Removes from the vector at certain index(not meant to be used by user)
        void removeImageAtIndex(int index);

        //gets mat at certain time
        Mat getMatByTime(double time);

        //gets mat at certain frame
        Mat getMatAtFrame(int frame_index);

        //gets image pointer from certain index
        Image *getImgAtIndex(int index);

        void writeVideo(string output_name);

        //User doesn't need these functions
        void displayCurrentVideo();

        int getPlace(double time);

        int getIndex(Image *img);

        void resize(int width, int height);

        void addBlank(VideoWriter video_writer, double time);

        void showBlank(double time);

        int animationNumber();

        void clear();

        //Animator structure which is capable of displaying
        //current image for that time and applying the Animation
        struct ImageAnimator {
        public:
            ImageAnimator();

            ImageAnimator(Image *image, double start_time, double display_time, int fps);

            ImageAnimator(Image *image, double start_time, double display_time, int fps, Animation animation_type);

            ~ImageAnimator();

            void display();

            void write(VideoWriter video_writer);

            void setAnimation(Animation animation_type);

            Mat getMatAt(int frame_number);

            Mat normalDisplay(int frame_number);

            Mat rotateAnimation(int frame_number);

            //Functions below should be of type Mat as well, not tested yet
            void zoomAnimation(int frame_number);

            void cropAnimation();

            void initFunctions();

            Mat createBlank(int *color, int *size);

            Image *image;
            double time, start_time, fps;
            Animation animation_type;

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
