#include <QApplication>
#include "videoeditor.h"

#include "src/Audio/Audio.hpp"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    VideoEditor videoEditor;
    videoEditor.show();
    return QApplication::exec();
}
