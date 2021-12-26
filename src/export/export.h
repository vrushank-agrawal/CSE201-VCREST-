//
// Created by Vrushank on 12/17/2021.
//

#ifndef EXPORT_CLASS
#define EXPORT_CLASS

#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
//#include <windows.h>
#include <algorithm>
#include <sstream>

namespace exp {

    class exporter {
        std::string video_path;
        std::string audio_path;
        std::string export_address;

    public:
        exporter(std::string video_path, std::string audio_path, std::string export_address);
        ~exporter();
        void merge_av(std::string video_path, std::string audio_path, std::string export_address);

    };

}

#endif //EXPORT_CLASS