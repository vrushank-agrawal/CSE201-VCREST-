//
// Created by lasha on 14-Nov-21.
//

#include "Audio.hpp"

using namespace std;

namespace audio {

    int Audio::num = 0;
    string folder = "temp_media";
    string Audio::out = folder + "/output";

    Audio::Audio(const std::string &uri) {

        mkdir(folder.c_str());

        std::string ext = uri.substr(uri.length() - 3);

        char cstr[uri.length() + 1];
        strcpy(cstr, uri.c_str());

        string mp3out = out + ".mp3";
        string wavout = out + to_string(num) + ".wav";
        num++;

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

        this->uri = wavout;

        ifstream infile(this->uri, ios_base::binary);
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

        del_aubio_tempo(tempo);

        return output;

    }

    string merge(const Audio &a1, const Audio &a2) {
        int size = a1.size + a2.size - 44;
        char *merged_file = new char[size];
        for (int i = 0; i < a1.size; i++) {
            merged_file[i] = a1.file[i];
        }
        for (int i = 44; i < a2.size; i++) {
            merged_file[a1.size + i] = a2.file[i];
        }
        int curr_size = *((int *) (merged_file + 40));
        curr_size += *((int *) (a2.file + 40));
        *((int *) (merged_file + 40)) = curr_size;
        string out = Audio::out + to_string(Audio::num) + ".wav";
        ofstream outfile(out, ios_base::binary);
        Audio::num++;
        outfile.write(merged_file, size);
        outfile.close();
        return out;
    }

    string trim(const Audio &a, int ms, bool isStart) {
        int trim_size = ms * 4 * 44100 / 1000;
        int audio_size = *((int *) (a.file + 40));
        int final_size = isStart ? trim_size : (audio_size - trim_size);
        char *trimmed_file = new char[final_size + 44];
        for (int i = 0; i < 44; i++) {
            trimmed_file[i] = a.file[i];
        }
        if (isStart) {
            for (int i = 44; i < 44 + final_size; i++) {
                trimmed_file[i] = a.file[i];
            }
        } else {
            for (int i = 44; i < a.size - trim_size; i++) {
                trimmed_file[i] = a.file[i + trim_size];
            }
        }
        *((int *) (trimmed_file + 40)) = final_size;
        string out = Audio::out + to_string(Audio::num) + ".wav";
        ofstream outfile(out, ios_base::binary);
        Audio::num++;
        outfile.write(trimmed_file, final_size + 44);
        outfile.close();
        return out;
    }

    arr3d Audio::getSpectrumVisualizer() {

        arr3d res;

        sample_rate = 0;
        hop_size = 512;

        source = new_aubio_source(uri.c_str(), sample_rate, hop_size);
        channels = aubio_source_get_channels(source);
        sample_rate = aubio_source_get_samplerate(source);
        duration = aubio_source_get_duration(source);

        int win_size = hop_size * 2;

        aubio_fft_t *fft = new_aubio_fft(win_size);

        uint_t i, n_iters = 100;
        fvec_t *in = new_fvec(win_size);
        cvec_t *fftgrain = new_cvec(win_size);
        fvec_t *fout = new_fvec(win_size);

        in->data[0] = 1;
        in->data[1] = 2;
        in->data[2] = 3;
        in->data[3] = 4;
        in->data[4] = 5;
        in->data[5] = 6;
        in->data[6] = 5;
        in->data[7] = 6;

        for (i = 0; i < n_iters; i++) {

            aubio_fft_do(fft, in, fftgrain);
            cvec_print(fftgrain);

            aubio_fft_rdo(fft, fftgrain, fout);
        }

        del_aubio_fft(fft);
        del_fvec(in);
        del_cvec(fftgrain);
        del_fvec(fout);
        aubio_cleanup();

        return res;

    }


}
