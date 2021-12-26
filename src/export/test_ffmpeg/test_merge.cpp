//
// Created by Vrushank on 12/17/2021.
//

#include "../export.h"

std::string get_curr_dir() {
    char add[256];
    getcwd(add, 256);

    // convert char to string
    std::string address;
    for (int i =0; i< strlen(add); i++){
        address += add[i];
    }

    return address;
}

int main() {

    std::string address = get_curr_dir();

    std::string audio_path;
    std::string video_path;
    std::string export_address;

    audio_path = address + R"(\..\test_files\audio.wav)";
    video_path = address + R"(\..\test_files\video.mp4)";
    export_address = address + R"(\..\test_files\output.mkv)";

//    char video_path[200];
//    strcpy(video_path, "/Users/minhtung0404/Documents/CS/github/video_editor_BX23/src/export/test_ffmpeg/test_files/video.mp4");
//    char audio_path[200];
//    strcpy(audio_path, "/Users/minhtung0404/Documents/CS/github/video_editor_BX23/src/export/test_ffmpeg/test_files/audio.wav");
//    std::string audio_path = address;
//    char export_address[200];
//    strcpy(export_address, "/Users/minhtung0404/Documents/CS/github/video_editor_BX23/src/export/test_ffmpeg/test_files/output.mkv");


    exp::exporter(video_path, audio_path, export_address);

    exit(0);

}