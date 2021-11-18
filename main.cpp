#include <QApplication>
#include <QPushButton>

#include "src/Audio/Audio.hpp"

int main(int argc, char *argv[]) {

    audio::Audio *file = new audio::Audio("C:/Users/lasha/Documents/GitHub/video_editor_BX23/media/audio/test.wav");

    QApplication a(argc, argv);
    QPushButton button("Hello World!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
