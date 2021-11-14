#include <QApplication>
#include <QPushButton>

#include "src/Audio/Audio.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    audio::Audio audio1;
    audio1.getX();
    QPushButton button("Helloworld", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
