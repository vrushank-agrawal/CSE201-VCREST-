//
// Created by Vrushank on 12/17/2021.
//

#include "export.h"

exp::exporter::exporter(std::string video_path, std::string audio_path, std::string export_address) {
    this -> export_address = export_address;
    this -> video_path = video_path;
    this -> audio_path = audio_path;

    remove(this->export_address.c_str());
    merge_av(this -> video_path, this -> audio_path, this -> export_address);
}

exp::exporter::~exporter() {}

void exp::exporter::merge_av (std::string video_path, std::string audio_path, std::string export_address) {

    std::string cmd = "ffmpeg -i " + video_path + " -i " + audio_path + " -c copy " + export_address;

    system(cmd.c_str());
}