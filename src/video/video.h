#ifndef VIDEO_CLASS
#define VIDEO_CLASS

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <string>
#include "image.h"

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

        Video(img::Image **images, double *start_times, double *times_of_display, int size, int width, int height, int fps);

        ~Video();

        void test();

        //Main working functions

        //adds Image pointer at specific time for some duration
        void addImage(img::Image *img, double start_time, double time_to_display);

        //Deletes everything associated to image pointer.
        void deleteImage(img::Image *img);

        //Applies Animation (receives image pointer and Animation type)
        void applyAnimation(img::Image *img, Animation animation_type);

        //gets mat at certain time
        cv::Mat getMatByTime(double time);

        //gets mat at certain frame
        cv::Mat getMatAtFrame(int frame_index);

        //gets image pointer from certain index
        img::Image *getImgAtIndex(int index);

        bool writeVideo(std::string output_name, int fourcc);

        int getPlace(double time);

        int getIndex(img::Image *img);

        void resize(int width, int height);

        void addBlank(cv::VideoWriter video_writer, double time);

        void showBlank(double time);

        int animationNumber();

        void clear();

    private:
        //adds Image pointer in the end(normally user won't use this)
        void insertImage(img::Image *img, double start_time, double time_to_display);

        //adds Image pointer at certain index (not meant to be used by user)
        void insertImage(img::Image *img, double start_time, double time_to_display, int index);

        //Removes from the vector at certain index(not meant to be used by user)
        void removeImageAtIndex(int index);

        //User doesn't need these functions
        void displayCurrentVideo();


        //Animator structure which is capable of displaying
        //current image for that time and applying the Animation
        struct ImageAnimator {
        public:
            ImageAnimator();

            ImageAnimator(img::Image *image, double start_time, double display_time, int fps);

            ImageAnimator(img::Image *image, double start_time, double display_time, int fps, Animation animation_type);

            ~ImageAnimator();

            void display();

            void write(cv::VideoWriter video_writer);

            void setAnimation(Animation animation_type);

            cv::Mat getMatAt(int frame_number);

            cv::Mat normalDisplay(int frame_number);

            cv::Mat rotateAnimation(int frame_number);

            //Functions below should be of type Mat as well, not tested yet
            void zoomAnimation(int frame_number);

            void cropAnimation();

            void initFunctions();

            cv::Mat createBlank(int *color, int *size);

            img::Image *image;
            double time, start_time, fps;
            Animation animation_type;

            cv::Mat (ImageAnimator::*anim_functions[total_number_of_animations + 1 ])(int);
        };

    private:
        std::vector<img::Image *> image_pointers;
        std::vector<ImageAnimator> animators;
        img::Image blank;
        int number_of_animations;
        static int width, height, fps;
    };

}


#endif // VIDEO_CLASS
