//
// Created by Vrushank on 12/17/2021.
//

#include "export.h"

exp::exporter::exporter(std::string video_path, std::string audio_path, std::string export_address) {

    const char* vid = video_path.c_str();
    const char* aud = audio_path.c_str();
    const char* exp = export_address.c_str();

    this -> export_address = exp;
    this -> video_path = vid;
    this -> audio_path = aud;

    merge_av(this -> video_path, this -> audio_path, this -> export_address);
}

exp::exporter::~exporter() {}

void exp::exporter::merge_av (const char* video_path, const char* audio_path, const char* export_address) {

    char cmd[256];
    strcpy(cmd,"ffmpeg -i ");
    strcat(cmd, video_path);
    strcat(cmd, " -i ");
    strcat(cmd, audio_path);
    strcat(cmd, " -c copy ");
    strcat(cmd, export_address);
    system(cmd);

}