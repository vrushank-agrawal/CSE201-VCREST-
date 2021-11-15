#include <QApplication>
#include <QPushButton>

#include "src/Audio/Audio.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello World!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
