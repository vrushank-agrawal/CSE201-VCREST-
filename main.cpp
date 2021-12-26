#include <QApplication>
#include "videoeditor.h"

#include "Audio.hpp"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    application.setStyleSheet("QToolTip { color: #000000; background-color: #ffffff; border: 0px; }");
    VideoEditor videoEditor;
    videoEditor.show();
    return QApplication::exec();
}
