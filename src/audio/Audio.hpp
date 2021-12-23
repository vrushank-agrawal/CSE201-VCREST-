//
// Created by lasha on 14-Nov-21.
//

#ifndef VIDEO_EDITOR_BX23_AUDIO_HPP
#define VIDEO_EDITOR_BX23_AUDIO_HPP

#include <string>
#include <vector>
#include "aubio/aubio.h"
#include "lameHelper.hpp"

using namespace std;

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
        static string out;

    public:
        Audio(const std::string &uri);

        std::vector<int> getBeatPositions();

    };

    string merge(const Audio &a1, const Audio &a2);

    string trim(const Audio &a, int ms, bool isStart);

}

#endif //VIDEO_EDITOR_BX23_AUDIO_HPP
