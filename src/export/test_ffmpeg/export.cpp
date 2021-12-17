//
// Created by Vrushank on 12/17/2021.
//

#include "export.h"

using namespace std;

int main() {


    char cmd[100];
    strcpy(cmd,"ffmpeg -i test_files/video.mp4 -i test_files/audio.wav -c copy output_1.mkv");
    system(cmd);
    exit(0);
    return 0;

}