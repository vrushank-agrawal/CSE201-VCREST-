//
// Created by Vrushank on 12/17/2021.
//
#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <windows.h>
#include <algorithm>
#include <sstream>

#ifndef EXPORT_CLASS
#define EXPORT_CLASS

namespace exp {

    class exporter {
        const char* video_path;
        const char* audio_path;
        const char* export_address;

    public:
        exporter(std::string video_path, std::string audio_path, std::string export_address);
        ~exporter();
        void merge_av(const char* video_path, const char* audio_path, const char* export_address);

    };

}

#endif //EXPORT_CLASS