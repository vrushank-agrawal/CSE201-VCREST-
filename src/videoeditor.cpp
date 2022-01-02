//
// Created by nhatv on 11 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoEditor.h" resolved

#include "videoeditor.h"
#include "ui_VideoEditor.h"


VideoEditor::VideoEditor(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::VideoEditor) {
    ui->setupUi(this);
    setupMenus();
    setupWidgets();

    // add video to preview
    QStringList arguments = QApplication::arguments();
    QString prefix = "audioPath=";
    QString prefix2 = "imagePath=";

    for (const auto& arg : arguments) {
        if (arg.startsWith(prefix)) {
            importAudio(arg.right(arg.size() - prefix2.size()));
        }
        if (arg.startsWith(prefix2)) {
            importImage(arg.right(arg.size() - prefix2.size()));
        }
    }
}

VideoEditor::~VideoEditor() {
    delete ui;
    delete resultVideo;
    delete imageManager;
    delete audioManager;
    delete audioPlayer;
}

void VideoEditor::updateCurrentTime(double time) {
    if (this->timeInSec != time) {
        if (time * fps > numberFrame) {
            time = 1.0 * numberFrame / fps;
            ui->playButton->clicked();
        }

        this->timeInSec = time;
        this->position = int(time * fps);
        updateFrame();
        emit positionChanged(position);
        emit currentTimeChanged(timeInSec);
    }
}

void VideoEditor::updatePosition(int newPosition) {
    updateCurrentTime(1.0 * newPosition / fps);
}