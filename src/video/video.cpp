//
// Created by korkot on 11/21/2021.
//
#include "video.h"

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
        this->Add(images[index], times_of_display[index]);
        number_of_animations++;
    }
}

Video::~Video() {
    this->Clear();
}

void Video::Add(Mat image_mat, int time_to_display) {
    this->image_mats.push_back(image_mat);
    Image new_image = Image(image_mat);
    ImageAnimator new_animator = ImageAnimator(new_image, time_to_display);
    this->animators.push_back(new_animator);
    this->number_of_animations ++;
}

void Video::Add(Mat image_mat, int time_to_display, int index) {
    if (index > this->number_of_animations){
        cout << "Index is out of reach";
    } else if (index == this->number_of_animations) {
        this->Add(image_mat, time_to_display);
    } else {
        this->image_mats.insert(this->image_mats.begin() + index, image_mat);
        Image new_image = Image(image_mat);
        ImageAnimator new_animator = ImageAnimator(new_image, time_to_display);
        this->animators.insert(this->animators.begin() + index, new_animator);
        this->number_of_animations++;
    }
}

void Video::Remove(int index) {
    if (index >= this->number_of_animations){
        cout << "Index out of reach" << endl;
        return;
    }
    this->image_mats.erase(this->image_mats.begin() + index);
    this->animators.erase(this->animators.begin() + index);
    number_of_animations --;
}

void Video::Clear() {
    this->image_mats.clear();
    this->animators.clear();
    this->number_of_animations = 0;
    this->width = 0;
    this->height = 0;
}

void Video::DisplayCurrentVideo() {
    cout << number_of_animations << endl;
    for (int i = 0; i < number_of_animations; i++){
        animators[i].Display();
        //cout << "Done" << endl;
        //animators[i].RotateAnimation();
    }
    destroyAllWindows();
}

void Video::WriteVideo(string output_name) {
    VideoWriter video_writer(output_name, VideoWriter::fourcc('m','p','4','v'),
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


Video::ImageAnimator::ImageAnimator(Image image, int display_time) {
    this->image = image;
    this->time = display_time;
    this->animation_type = -1;
}


Video::ImageAnimator::~ImageAnimator() {
}

void Video::ImageAnimator::Display() {
    int i = 0;
    while(i < time){
        imshow( "Frame", this->image.getMat());
        char c = (char)waitKey(1);
        if( c == 27 )
            break;
        i++;
    }
}

void Video::ImageAnimator::Write(VideoWriter video_writer) {
    int i = 0;
    while(i < this->time){
        video_writer.write(this->image.getMat());
        char c = (char)waitKey(1);
        if( c == 27 )
            break;
        i++;
    }
}


const double FRAMEPERSECOND = 10;

void Video::ImageAnimator::RotateAnimation() {
    int angle = 5;
    int num_frame = FRAMEPERSECOND*time;
    double frame_angle = angle;

    Mat modified_image = this->image.getModifiedImg();
    for (int i=1;i<=this->time;i++){
        Image new_image = Image(modified_image);
        new_image.rotateImg(frame_angle);
        imshow( "Frame", new_image.getModifiedImg());
        char c = (char)waitKey(1);
        if( c == 27 )
            break;

        frame_angle += angle;
    }
}

void Video::ImageAnimator::ZoomAnimationDisplay() {
    int ratio = 0.2;
    int num_frame = FRAMEPERSECOND*time;
    double change_per_frame = 1+ratio;
    int img_h = this->image.getMat().size().height;
    int img_w = this->image.getMat().size().width;
    for (int i=1;i<=num_frame;i++){
        img_h *= change_per_frame;
        img_w *= change_per_frame;
        this->image.resizeImg(img_w, img_h);
        imshow( "Frame", this->image.getModifiedImg());
        char c = (char)waitKey(1);
        if( c == 27 )
            break;
        change_per_frame += ratio;
    }
}

void Video::ImageAnimator::CropAnimation() {
    int num_frame = FRAMEPERSECOND*time;
    int h = this->image.getMat().rows;
    int w = this->image.getMat().cols;
    int window_h = h/2;

    for (int i=1;i<=num_frame;i++){
        while (10*i+window_h<h and 10*i+window_h<w) {
            Mat new_img = this->image.getMat().clone();
            cv::Rect myROI(10 * i, 10 * i, window_h, window_h);
            Mat cropped = new_img(myROI);
            imshow("Frame", cropped);
            char c = (char) waitKey(1);
            if (c == 27)
                break;
        }

    }


     /* def create_blank(width, height, rgb_color=(0, 0, 0)):
    """Create new image(numpy array) filled with certain color in RGB"""
    # Create black blank image
    image = np.zeros((height, width, 3), np.uint8)

    # Since OpenCV uses BGR, convert the color first
    color = tuple(reversed(rgb_color))
    # Fill image with color
    image[:] = color

    return image
     * int diff_h =
    for (int i=1;i<=num_frame;i++){
        background[]
    }*/
}

