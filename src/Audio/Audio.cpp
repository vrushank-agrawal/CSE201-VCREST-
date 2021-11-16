//
// Created by lasha on 14-Nov-21.
//

#include "Audio.hpp"

namespace audio {

    Audio::Audio(string uri) {

        sample_rate = 0;
        uint_t hop_size = 256;
        uint_t n_frames = 0, read = 0;

        aubio_source_t *s = new_aubio_source(uri.c_str(), sample_rate, hop_size);
        sample_rate = aubio_source_get_samplerate(s);

        fvec_t *vec = new_fvec(hop_size);

        do {
            aubio_source_do(s, vec, &read);
            fvec_print(vec);
            n_frames += read;
        } while (read == hop_size);

        aubio_source_close(s);

        if (vec)
            del_fvec(vec);
        if (s)
            del_aubio_source(s);

    }

    vector<double> Audio::getBeatPositions() {

    }

}
