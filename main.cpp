#include <QApplication>
#include "videoeditor.h"
#include "audio.hpp"

#include<iostream>

using namespace std;

int main(int argc, char *argv[]) {
    audio::Audio a("C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/test.wav");
    audio::Audio b("C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/test1.wav");
    audio::merge(a, b);
    audio::trim(b, 12000, false);
    return 0;
}
