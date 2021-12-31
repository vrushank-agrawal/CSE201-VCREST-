#include <QApplication>
#include "videoeditor.h"

#include "Audio.hpp"

int main(int argc, char *argv[]) {
    // First audio file
    audio::Audio a("../media/audio/test1.mp3");
    // Second audio file
    audio::Audio b("../media/audio/test2.wav");
    /*
     * These create raw audio files in the folder "cmake-build-debug\temp_media"
     * output0.wav and output1.wav respectively
    */

    // Merges two audio files, creates output2.wav and returns the name of the file
    std::string urlm = audio::merge(a, b);

    // Merged audio
    audio::Audio c(urlm);
    // Trim first 25 seconds of the audio
    std::string urlt1 = audio::trim(c, 25000, false);

    // Trimmed audio
    audio::Audio d(urlt1);

    // Leave only first 10 seconds of the audio
    audio::trim(d, 10000, true);

    return 0;

}
