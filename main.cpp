#include <QApplication>
#include "videoeditor.h"

#include "Audio.hpp"

#include<iostream>

int main(int argc, char *argv[]) {
    // uncomment to test audio
    // audio::test();

    audio::Audio a("C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/test2.wav");

    for (auto x: a.getBeatPositions()) {
        std::cout << x << std::endl;
    }

    QApplication application(argc, argv);
    application.setStyleSheet("QToolTip { color: #000000; background-color: #ffffff; border: 0px; }");
    VideoEditor videoEditor;
    videoEditor.show();
    return QApplication::exec();
}
