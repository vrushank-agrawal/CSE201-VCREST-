#include "video.h"

// Draft for video class

using namespace vid;

vid::Video::Video(List filenames_images, string filename_audio,  int time_of_display) {
    this -> filename_audio = filename_audio;
    this -> filenames_images = filenames_images;

    this -> validVid( filename_audio, filenames_images);
}

bool vid::Video::validVid(const string &filename_audio, const List &filenames_images) {

}
