//
// Created by Vrushank on 12/17/2021.
//

#include "export.h"

void merge_av (std::string video_path, std::string audio_path, std::string export_address) {

    char cmd[256];
    strcpy(cmd,"ffmpeg -i ");
    strcat(cmd, video_path);
    strcat(cmd, " -i ");
    strcat(cmd, audio_path);
    strcat(cmd, " -c copy ");
    strcat(cmd, export_address);
    system(cmd);

}