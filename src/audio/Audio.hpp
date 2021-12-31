//
// Created by lasha on 14-Nov-21.
//

#ifndef VIDEO_EDITOR_BX23_AUDIO_HPP
#define VIDEO_EDITOR_BX23_AUDIO_HPP

#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <QDir>
#include "aubio/aubio.h"
#include "lameHelper.hpp"

typedef std::array<std::array<std::array<int, 2>, 2>, 2> arr3d;

namespace audio {

    class Audio {
    private:

        std::string uri;

        // Audio parameters
        int channels;
        int sample_rate;
        int duration;

        // Source parameters
        int hop_size;

        // Function parameters
        int min_len = 200;

        aubio_source_t *source;

    public:
        char *file;
        int size;

        static int num;
        static std::string out;

    public:
        Audio(const std::string &uri);

        std::vector<int> getBeatPositions();

        arr3d getSpectrumVisualizer();

    };

    std::string merge(const Audio &a1, const Audio &a2);

    std::string trim(const Audio &a, int ms, bool isStart);

    void test();

}

#endif //VIDEO_EDITOR_BX23_AUDIO_HPP
