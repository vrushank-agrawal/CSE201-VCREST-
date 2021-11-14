//
// Created by lasha on 14-Nov-21.
//

#include "aubio/aubio.h"
#include "Audio.hpp"

#include <iostream>

using namespace std;

int audio::Audio::getX() {
    aubio_source_t *a = new_aubio_source("C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/test.wav", 0,
                                         50);
    cout << aubio_source_get_samplerate(a) << endl;
    return 0;
}
