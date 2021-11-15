//
// Created by lasha on 14-Nov-21.
//

#ifndef VIDEO_EDITOR_BX23_AUDIO_HPP
#define VIDEO_EDITOR_BX23_AUDIO_HPP

#include <string>
#include <vector>
#include "aubio/aubio.h"

using namespace std;

namespace audio {

    class Audio {
    private:

    public:
        Audio(string uri);

        vector<double> getBeatPositions();
    };

}


#endif //VIDEO_EDITOR_BX23_AUDIO_HPP
