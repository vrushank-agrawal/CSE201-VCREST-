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

void VideoEditor::updateVideoLength(double length) {
    numberFrame = int(length * fps);

    ui->controlSlider->setRange(0, numberFrame);
    ui->controlSlider->setTracking(true);

    ui->timeline->updateVideoLength(length);
    ui->preview->updateVideoLength(length);
}

void VideoEditor::addImagesByAudio() {
    auto listItem = audioManager->getSelectedItem();
    if (listItem == nullptr || imageManager->getImagesCount() == 0) {
        QMessageBox errorMsg;
        errorMsg.setWindowTitle("Error");
        errorMsg.setText("Not enough images or audio not selected");
        errorMsg.exec();
    }
    else if (!ui->timeline->isEmpty()) {
        QMessageBox errorMsg;
        errorMsg.setWindowTitle("Error");
        errorMsg.setText("Timeline is not empty");
        errorMsg.exec();
    }
    else {
        auto item = audioManager->getAudio(listItem);
        std::vector<int> timeVector = item->getBeatPositions();
        double videoLengthInMs = 0;
        for (int i = 0; i < timeVector.size(); i++) {
            double start = (i == 0) ? 0 : timeVector[i-1], end = timeVector[i];
            auto image = new img::Image(imageManager->getImage(i % imageManager->getImagesCount())->getMat());
            ui->timeline->addImage(image, start / 1000.0, end / 1000.0);
        }
        videoLengthInMs = *timeVector.rbegin();
        ui->timeline->addAudio(item, listItem->text(), videoLengthInMs, 0, videoLengthInMs / 1000.0);
    }
}