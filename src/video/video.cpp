//
// Created by korkot on 11/21/2021.
//
#include "video.h"
#include "../image/image.h"

using namespace vid;
using namespace std;
using namespace img;



void Video::test(){
    cout << "OK" << endl;
}

Video::Video(int width, int height) {
    this->number_of_animations = 0;
    this->Resize(width, height);
    this->Clear();
}

Video::Video(Mat *images, int *times_of_display, int size, int width, int height) : Video(width, height) {
    for (int index = 0; index < size; index++) {
        cout << "Here" << endl;
        this->Add(images[index], times_of_display[index]);
        number_of_animations++;
    }
}

Video::~Video() {
    this->Clear();
}

void Video::Add(Mat img, int time_to_display) {
    this->images.push_back(img);
    ImageAnimator new_animator = ImageAnimator(img, time_to_display);
    this->animators.push_back(new_animator);
    this->number_of_animations ++;
}

void Video::Add(Mat img, int time_to_display, int index) {
    if (index > this->number_of_animations){
        cout << "Index is out of reach";
    } else if (index == this->number_of_animations) {
        this->Add(img, time_to_display);
    } else {
        this->images.insert(this->images.begin() + index, img);
        ImageAnimator new_animator = ImageAnimator(img, time_to_display);
        this->animators.insert(this->animators.begin() + index, new_animator);
        this->number_of_animations++;
    }
}

void Video::Remove(int index) {
    if (index >= this->number_of_animations){
        cout << "Index out of reach" << endl;
        return;
    }
    this->images.erase(this->images.begin() + index);
    this->animators.erase(this->animators.begin() + index);
    number_of_animations --;
}

void Video::Clear() {
    for (int i = 0; i < number_of_animations; i++){
    }
    this->images.clear();
    this->animators.clear();
    this->number_of_animations = 0;
    this->width = 0;
    this->height = 0;
}

void Video::DisplayCurrentVideo() {
    for (int i = 0; i < number_of_animations; i++){
        animators[i].Display();
    }
    destroyAllWindows();
}

void Video::WriteVideo(string output_name) {
    VideoWriter video_writer(output_name, VideoWriter::fourcc('M','J','P','G'),
                             10, Size(this->width, this->height));
    for (int i = 0; i < this->number_of_animations; i++){
        this->animators[i].Write(video_writer);
    }
    video_writer.release();
    destroyAllWindows();
}

void Video::Resize(int width, int height) {
    this->width = width;
    this->height = height;
}

int Video::AnimationNumber(){
    return this->number_of_animations;
}

Video::ImageAnimator::ImageAnimator(Mat img, int display_time) {
    this->img = img;
    this->time = display_time;
    this->animation_type = -1;
}

Video::ImageAnimator::~ImageAnimator() {
}

void Video::ImageAnimator::Display() {
    int i = 0;
    while(i < time){
        imshow( "Frame", img);
        char c = (char)waitKey(1);
        if( c == 27 )
            break;
        i++;
    }
}

void Video::ImageAnimator::Write(VideoWriter video_writer) {
    int i = 0;
    while(i < this->time){
        video_writer.write(img);
        char c = (char)waitKey(1);
        if( c == 27 )
            break;
        i++;
    }
}


const double FRAMEPERSECOND = 10;

void Video::ImageAnimator::RotateAnimation(double angle) {
    int num_frame = FRAMEPERSECOND*time;
    double change_per_frame = angle/num_frame;
    Image image_mat = img::Image(get_mat());
    for (int i=1;i<=num_frame;i++){
        image_mat.rotateImg(change_per_frame);
        img = image_mat.getMat();
        imshow( "Frame", img);
    }
}

void Video::ImageAnimator::ZoomAnimationDisplay(double ratio) {
    int num_frame = FRAMEPERSECOND*time;
    double change_per_frame = 1+(ratio-1)/num_frame;
    int img_h = img.size().height;
    int img_w = img.size().width;
    Image image_mat = img::Image(get_mat());
    for (int i=1;i<=num_frame;i++){
        img_h *= change_per_frame;
        img_w *= change_per_frame;
        image_mat.resizeImg(img_w, img_h);
        img = image_mat.getMat();
        imshow( "Frame", img);
    }
}

void Video::ImageAnimator::FlyAnimation(Mat background) {
    int num_frame = FRAMEPERSECOND*time;
    int h = img.rows;
    int w = img.cols;
    /*int diff_h =
    for (int i=1;i<=num_frame;i++){
        background[]
    }*/
}