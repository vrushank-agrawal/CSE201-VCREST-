//
// Created by lasha on 14-Nov-21.
//

#include "audio.hpp"

#include <iostream>
#include <fstream>

using namespace std;

namespace audio {

    Audio::Audio(const std::string &uri) {

        std::string ext = uri.substr(uri.length() - 3);

        char cstr[uri.length() + 1];
        strcpy(cstr, uri.c_str());

        string mp3out = "C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/output.mp3";
        string wavout = "C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/output.wav";

        if (ext == "wav") {

            lameHelper conv;
            conv.encode(uri, mp3out);
            conv.decode(mp3out, wavout);
            remove(mp3out.c_str());

        } else if (ext == "mp3") {

            lameHelper conv;
            conv.decode(cstr, wavout);

        } else {
            return;
        }

        ifstream infile(uri);
        if (!infile.is_open()) {
            cout << "ERROR WHILE READING THE FILE!" << endl;
            return;
        }

        infile.seekg(0, std::ios::end);
        size_t length = infile.tellg();
        infile.seekg(0, std::ios::beg);

        file = new char[length];
        size = length;

        infile.read(file, length);
        infile.close();

        for (int i = 44; i < 100; i++) {
            cout << int(file[i]) << endl;
        }


    }

    std::vector<int> Audio::getBeatPositions() {

        sample_rate = 0;
        hop_size = 512;

        source = new_aubio_source(uri.c_str(), sample_rate, hop_size);
        channels = aubio_source_get_channels(source);
        sample_rate = aubio_source_get_samplerate(source);
        duration = aubio_source_get_duration(source);

        std::vector<double> beats_ms;

        int win_size = hop_size * 2;

        aubio_tempo_t *tempo = new_aubio_tempo("default", win_size, hop_size, sample_rate);

        fvec_t *in = new_fvec(hop_size); // input audio buffer
        fvec_t *out = new_fvec(1); // output position

        uint_t read = 0;
        do {
            aubio_source_do(source, in, &read);
            aubio_tempo_do(tempo, in, out);
            beats_ms.push_back(aubio_tempo_get_last_ms(tempo));
        } while (read == hop_size);

        std::vector<int> output;
        output.push_back(int(beats_ms[0]));

        for (int i = 1; i < beats_ms.size(); i++) {
            if (beats_ms[i] - output.back() >= min_len) {
                output.push_back(int(beats_ms[i]));
            }
        }

        return output;

    }

    void merge(Audio a1, Audio a2) {
        char *merged_file = new char[a1.size + a2.size - 44];
        for (int i = 0; i < a1.size; i++) {
            merged_file[i] = a1.file[i];
        }
        for (int i = 44; i < a2.size; i++) {
            merged_file[a1.size + i] = a2.file[i];
        }
        int curr_size = *(int *) merged_file[40];
        curr_size += *(int *) a2.file[40];
        *(int *) merged_file[40] = curr_size;
    }

}
