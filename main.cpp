#include <QApplication>
#include <QPushButton>
#include "videoeditor.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    VideoEditor videoEditor;
    videoEditor.show();
    return QApplication::exec();
}
