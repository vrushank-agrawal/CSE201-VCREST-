//
// Created by korkot on 11/21/2021.
//
#include "video.h"

using namespace vid;
using namespace std;
using namespace img;


void Video::test() {
    cout << "OK" << endl;
}

Video::Video(int width, int height, int fps) {
    this->number_of_animations = 0;
    this->Clear();
    this->Resize(width, height);
    this->fps = fps;
    Mat blank_img_mat(500, 1000, CV_8UC3, Scalar(0, 0, 100));
    this->blank = Image(blank_img_mat);
}

Video::Video(Image **images, double *start_times, double *times_of_display, int size, int width, int height, int fps)
        : Video(width, height, fps) {
    for (int index = 0; index < size; index++) {
        this->Insert(images[index], start_times[index], times_of_display[index]);
        number_of_animations++;
    }
}

Video::~Video() {
    this->Clear();
}

void Video::Add(Image *img, double start_time, double time_to_display) {
    int index = this->GetPlace(start_time);
    this->Insert(img, start_time, time_to_display, index);
}

void Video::Delete(Image *img) {
    int to_remove = this->GetIndex(img);
    if (to_remove != -1) {
        this->Remove(to_remove);
    }
}


void Video::Insert(Image *image, double start_time, double time_to_display) {
    image->resizeImg(this->width, this->height);
    this->image_pointers.push_back(image);
    ImageAnimator new_animator = ImageAnimator(image, start_time, time_to_display, this->fps);
    this->animators.push_back(new_animator);
    this->number_of_animations++;
}

void Video::Insert(Image *image, double start_time, double time_to_display, int index) {
    image->resizeImg(this->width, this->height);
    if (index > this->number_of_animations) {
        cout << "Index is out of reach";
    } else if (index == this->number_of_animations) {
        this->Insert(image, start_time, time_to_display);
    } else {
        this->image_pointers.insert(this->image_pointers.begin() + index, image);
        ImageAnimator new_animator = ImageAnimator(image, start_time, time_to_display, this->fps);
        this->animators.insert(this->animators.begin() + index, new_animator);
        this->number_of_animations++;
    }
}

void Video::Remove(int index) {
    if (index >= this->number_of_animations) {
        cout << "Index out of reach" << endl;
        return;
    }
    this->image_pointers.erase(this->image_pointers.begin() + index);
    this->animators.erase(this->animators.begin() + index);
    number_of_animations--;
}

void Video::Clear() {
    this->image_pointers.clear();
    this->animators.clear();
    this->number_of_animations = 0;
    this->width = 0;
    this->height = 0;
}

void Video::Resize(int width, int height) {
    this->width = width;
    this->height = height;
    for (int index = 0; index < this->number_of_animations; index++) {
        this->image_pointers[index]->resizeImg(width, height);
    }
}

int Video::AnimationNumber() {
    return this->number_of_animations;
}

void Video::DisplayCurrentVideo() {
    double cur_time = 0;
    for (int i = 0; i < number_of_animations; i++) {
        double blank_time_dur = animators[i].time - cur_time;
        if (blank_time_dur > 0){
            this->ShowBlank(blank_time_dur);
        }
        animators[i].Display();
    }
    destroyAllWindows();
}

void Video::WriteVideo(string output_name) {
    VideoWriter video_writer(output_name, VideoWriter::fourcc('m', 'p', '4', 'v'),
                             this->fps, Size(this->width, this->height));

    double cur_time = 0;
    for (int i = 0; i < this->number_of_animations; i++) {
        double blank_time_dur = animators[i].start_time - cur_time;
        if (blank_time_dur > 0){
            this->AddBlank(video_writer, blank_time_dur);
        }
        this->animators[i].Write(video_writer);
        cur_time = this->animators[i].start_time + this->animators[i].time;
    }
    video_writer.release();
    destroyAllWindows();
}

//Supposed to be a binary search
int Video::GetPlace(double time) {
    int index = 0;
    for (int i = 0; i < this->number_of_animations; i++) {
        if (time < this->animators[i].time) {
            break;
        }
        index++;
    }
    return index;
}

int Video::GetIndex(Image *img) {
    for (int i = 0; i < number_of_animations; i++) {
        if (this->image_pointers[i] == img) {
            return i;
        }
    }
    cout << "Video class doesn't contain this object" << endl;
    return -1;
}

void Video::ShowBlank(double time) {
    int i = 0;
    int num_fames = time * fps;
    while (i < num_fames) {
        imshow("Frame", this->blank.getModifiedImg());
        char c = (char) waitKey(1);
        if (c == 27)
            break;
        i++;
    }
}

void Video::AddBlank(VideoWriter video_writer, double time) {
    int i = 0;
    int num_fames = time * this->fps;
    while (i < num_fames) {
        video_writer.write(this->blank.getModifiedImg());
        i++;
    }
}

void Video::ApplyAnimation(Image *img, animation animation_type) {
    int index = this->GetIndex(img);
    this->animators[index].SetAnimation(animation_type);
}


//*****************************************ImageAnimator struct***********************************************

Video::ImageAnimator::ImageAnimator(Image *image, double start_time, double display_time, int fps) {
    this->image = image;
    this->start_time = start_time;
    this->time = display_time;
    this->fps = fps;
    this->animation_type = Normal;
    this->InitFunctions();
}


Video::ImageAnimator::ImageAnimator(Image *image, double start_time, double display_time, int fps,
                                    animation animation_type)
        : ImageAnimator(image, start_time, display_time, fps) {
    this->animation_type = animation_type;
}


Video::ImageAnimator::~ImageAnimator() {
    //To modify
}

Video::ImageAnimator::ImageAnimator() {

}

void Video::ImageAnimator::InitFunctions() {
    this->anim_functions[0] = &ImageAnimator::NormalDisplay;
    this->anim_functions[1] = &ImageAnimator::RotateAnimation;
}

void Video::ImageAnimator::SetAnimation(animation animation_type) {
    this->animation_type = animation_type;
}



void Video::ImageAnimator::Display() {
    int i = 0;
    int num_fames = this->time * fps;
    while (i < num_fames) {
        Mat disp = (this->*anim_functions[animation_type])(i);
        imshow("Frame", disp);
        char c = (char) waitKey(1);
        if (c == 27)
            break;
        i++;
    }
}

void Video::ImageAnimator::Write(VideoWriter video_writer) {
    int i = 0;
    int num_fames = this->time * this->fps;
    while (i < num_fames) {
        Mat disp = (this->*anim_functions[animation_type])(i);
        video_writer.write(disp);
        i++;
    }
}

Mat Video::ImageAnimator::NormalDisplay(int frame_number) {
    return this->image->getModifiedImg();
}


Mat Video::ImageAnimator::RotateAnimation(int frame_number) {
    int angle = 5 * frame_number;
    double frame_angle = angle;
    Mat modified_image = this->image->getModifiedImg();
    Image new_image = Image(modified_image);
    new_image.rotateImg(frame_angle);
    return new_image.getModifiedImg();
}


//************************************************************************************************

/*
//Not tested
void Video::ImageAnimator::ZoomAnimation() {
    int ratio = 0.2;
    int num_frame = fps * time;
    double change_per_frame = 1 + ratio;
    int img_h = this->image->getMat().size().height;
    int img_w = this->image->getMat().size().width;
    for (int i = 1; i <= num_frame; i++) {
        img_h *= change_per_frame;
        img_w *= change_per_frame;
        this->image->resizeImg(img_w, img_h);
        imshow("Frame", this->image->getModifiedImg());
        char c = (char) waitKey(1);
        if (c == 27)
            break;
        change_per_frame += ratio;
    }
}

//Not tested
void Video::ImageAnimator::CropAnimation() {
    int num_frame = fps * time;
    int h = this->image->getMat().rows;
    int w = this->image->getMat().cols;
    int window_h = h / 2;

    for (int i = 1; i <= num_frame; i++) {
        while (10 * i + window_h < h and 10 * i + window_h < w) {
            Mat new_img = this->image->getMat().clone();
            cv::Rect myROI(10 * i, 10 * i, window_h, window_h);
            Mat cropped = new_img(myROI);
            imshow("Frame", cropped);
            char c = (char) waitKey(1);
            if (c == 27)
                break;
        }

    }

}
 */
