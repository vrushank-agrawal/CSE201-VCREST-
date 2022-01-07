//
// Created by Vrushank on 12/17/2021.
//

#include "export.h"

void exp::merge_av (std::string video_path, std::string audio_path, std::string export_address) {

    std::string cmd = "ffmpeg -i " + video_path + " -i " + audio_path + " -c:v copy -c:a aac " + export_address;

    system(cmd.c_str());
}