#include <QApplication>
#include "videoeditor.h"

#include "Audio.hpp"

int main(int argc, char *argv[]) {
    //
    audio::Audio a("C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/test.wav");
    audio::Audio b("C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/test1.wav");
    audio::merge(a, b);
    return 0;
    //
}
