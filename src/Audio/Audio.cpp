//
// Created by lasha on 14-Nov-21.
//

#include "Audio.hpp"

#include <iostream>

using namespace std;

namespace audio {

    vector<int> filter(vector<int> input) {

        int min_length = 200;

        vector<int> output;
        output.push_back(input[0]);

        for (int i = 1; i < input.size(); i++) {
            if (input[i] - output.back() >= min_length) {
                output.push_back(input[i]);
            }
        }

        return output;

    }

    Audio::Audio(string uri) {

        sample_rate = 0;
        hop_size = 512;

        source = new_aubio_source(uri.c_str(), sample_rate, hop_size);
        channels = aubio_source_get_channels(source);
        sample_rate = aubio_source_get_samplerate(source);
        duration = aubio_source_get_duration(source);

    }

    vector<double> Audio::getBeatPositions() {

        vector<int> beats_ms;

        uint_t read = 0;

        int win_size = hop_size * 2;

        aubio_tempo_t *tempo = new_aubio_tempo("default", win_size, hop_size, sample_rate);

        fvec_t *in = new_fvec(hop_size); // input audio buffer
        fvec_t *out = new_fvec(1); // output position

        do {
            aubio_source_do(source, in, &read);
            aubio_tempo_do(tempo, in, out);
            beats_ms.push_back(aubio_tempo_get_last_ms(tempo));
        } while (read == hop_size);

        vector<int> output = filter(beats_ms);

        cout << output.size() << endl;

        for (int i = 0; i < output.size(); i++) {
            cout << output[i] << endl;
        }

    }

}
