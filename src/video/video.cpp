//
// Created by korkot on 11/21/2021.
//
#include "video.h"
#include "../image/image.h"

using namespace vid;
using namespace std;
using namespace img;


Video::Video() {
    this->number_of_animations = 0;
    this->Clear();
}


void Video::test(){
    cout << "OK" << endl;
}

Video::Video(Mat image, int time_of_display) : Video() {
    this->Add(image, time_of_display);
    number_of_animations++;
}

Video::Video(Mat *images, int *times_of_display, int size) : Video() {
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
}

void Video::Remove(int index) {
    this->images.erase(this->images.begin() + index);
    this->animators.erase(this->animators.begin() + index);
    number_of_animations --;
}

void Video::Clear() {
    for (int i = 0; i < number_of_animations; i++){
    }
    this->images.clear();
    this->animators.clear();
    int number_of_animations = 0;
}

void Video::DisplayCurrentVideo() {
    for (int i = 0; i < number_of_animations; i++){
        animators[i].Display();
    }
    destroyAllWindows();
}

Video::ImageAnimator::ImageAnimator(Mat img, int display_time) {
    this->img = img;
    this->time = display_time;
    this->animation_type = -1;
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

const double FRAMEPERSECOND = 60;
void Video::ImageAnimator::ZoomAnimation(double ratio) {
    string output;
    int num_frame = FRAMEPERSECOND*time;
    Mat modified_img_list[num_frame];
    double change_per_frame = 1+(ratio-1)/num_frame;
    double img_h = img.size().height;
    double img_w = img.size().width;
    modified_img_list[0] = img;
    for (int i=1;i<=num_frame;i++){
        img_h *= change_per_frame;
        img_w *= change_per_frame;
        //modified_img_list[i] = img.resizeImg(img_w, img_h);
    }
    //CreateVideo(output);
    Display();

}