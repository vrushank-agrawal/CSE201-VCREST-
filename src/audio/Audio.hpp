//
// Created by lasha on 14-Nov-21.
//

#ifndef VIDEO_EDITOR_BX23_AUDIO_HPP
#define VIDEO_EDITOR_BX23_AUDIO_HPP

#include <string>
#include <vector>
#include "aubio/aubio.h"
#include "lameHelper.hpp"

namespace audio {

    enum AudioType {
        mp3, wav
    };

    class Audio {
    private:

        std::string uri;
        char *file;

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
        Audio(const std::string &uri);

        std::vector<int> getBeatPositions();

    };

}

#endif //VIDEO_EDITOR_BX23_AUDIO_HPP
