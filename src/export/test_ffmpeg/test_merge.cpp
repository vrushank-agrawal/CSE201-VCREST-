//
// Created by Vrushank on 12/17/2021.
//

#include "test_merge.h"

using namespace std;

std::string get_curr_dir() {
    char tmp[256];
    getcwd(tmp, 256);

    // convert char to string
    std::string s;
    s += tmp;

    return s;
}

int main() {

    char add[256];
    getcwd(add, 256);

    // convert char to string
    std::string address;
    address += add;

    //remove \cmake-build-debug from string
    // get the last folder in the current working directory
    char* last_backslash = strrchr(add, '\\');
//    address.erase(remove(address.begin(), address.end(), "\cmake-build-debug"), address.end());

    cout << "Current working directory: " << last_backslash << endl;
    char video_path[200];
    strcpy(video_path, R"(C:\Users\minht\CLionProjects\video_editor_BX23\src\export\test_ffmpeg\test_files\video.mp4)");
    char audio_path[200];
    strcpy(audio_path, R"(C:\Users\minht\CLionProjects\video_editor_BX23\src\export\test_ffmpeg\test_files\audio.wav)");
    char export_address[200];
    strcpy(export_address, R"(C:\Users\minht\CLionProjects\video_editor_BX23\src\export\test_ffmpeg\test_files\output.mkv)");


    char cmd[256];
    strcpy(cmd,"ffmpeg -i ");
    strcat(cmd, video_path);
    strcat(cmd, " -i ");
    strcat(cmd, audio_path);
    strcat(cmd, " -c copy ");
    strcat(cmd, export_address);
    system(cmd);

    exit(0);

}