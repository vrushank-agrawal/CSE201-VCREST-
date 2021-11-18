//
// Created by lasha on 14-Nov-21.
//

#include "Audio.hpp"

#include <iostream>

using namespace std;

namespace audio {

    Audio::Audio(string uri) {

        sample_rate = 0;
        uint_t hop_size = 256;

        source = new_aubio_source(uri.c_str(), sample_rate, hop_size);
        sample_rate = aubio_source_get_samplerate(source);

        cout << aubio_source_get_duration(source)/sample_rate << endl;

        uint_t n_frames = 0, read = 0;

        fvec_t *vec = new_fvec(hop_size);

        do {
            aubio_source_do(source, vec, &read);
            //fvec_print(vec);
            n_frames += read;
        } while (read == hop_size);

        aubio_source_close(source);

        if (vec)
            del_fvec(vec);
        if (source)
            del_aubio_source(source);

    }

    vector<double> Audio::getBeatPositions() {

        uint_t read = 0;

        int win_size = 30;
        int hop_size = 20;

        aubio_tempo_t *tempo = new_aubio_tempo("default", win_size, hop_size, sample_rate);

        fvec_t *in = new_fvec(hop_size); // input audio buffer
        fvec_t *out = new_fvec(1); // output position

        do {
            aubio_source_do(source, in, &read);
            aubio_tempo_do(tempo, in, out);
        } while (read == hop_size);

    }

}
