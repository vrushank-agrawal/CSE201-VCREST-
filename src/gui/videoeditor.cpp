//
// Created by nhatv on 11 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoEditor.h" resolved

#include "videoeditor.h"
#include "ui_VideoEditor.h"
#include <QFileDialog>
#include <QMessageBox>

VideoEditor::VideoEditor(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::VideoEditor) {
    ui->setupUi(this);
          
    // add graphics view to preview
    ui->preview->setChild(ui->label,
                          ui->playButton,
                          ui->skipForward,
                          ui->skipBackward,
                          ui->progressBar);
    ui->preview->updateVideo(cv::VideoCapture("/Users/minhtung0404/Downloads/1.mp4"));

    setupMenus();
    setupWidgets();

//    connect(ui->controlSlider, &QSlider::valueChanged, this, &VideoEditor::setDisplayImage);
}

void VideoEditor::setupMenus() {
    ui->actionImport_Image->setShortcut(QKeySequence::Open);
    connect(ui->actionImport_Image, &QAction::triggered, this, &VideoEditor::importImage);

    connect(ui->actionImport_Audio, &QAction::triggered, this, &VideoEditor::importImage);
}

void VideoEditor::setupWidgets() {
    thumbnailManager = new ThumbnailManager(ui->imgListWidget);
    audioManager = new AudioManager(ui->audioListWidget);

    // testing
    setupImageListWidget();
    audioManager->addAudio("hello.mp3");
}

void VideoEditor::importImage() {
    QString filter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    QString fileName = importFile("Import Image", "/", filter);
    QPixmap img(fileName);
    if (!img.load(fileName)) {
        img = QPixmap(":/img-error.png");
    }
    thumbnailManager->addImage(img, fileName);
}

void VideoEditor::importAudio() {

}

QString VideoEditor::importFile(const QString& caption, const QString& dir, const QString& filter) {
    QString fileName = QFileDialog::getOpenFileName(this, caption, dir, filter);
    return fileName;
}


void VideoEditor::setupImageListWidget() {
    auto *testPixmap = new QPixmap(":/img-error.png");

    thumbnailManager->addImage(*testPixmap, "test1");
    thumbnailManager->addImage(*testPixmap, "test2");
    thumbnailManager->addImage(*testPixmap, "test2222222222222222222222222222222222222222222");

    for (int i = 3; i < 20; i++) {
        thumbnailManager->addImage(*testPixmap, "test" + QString::number(i));
    }
}

void VideoEditor::setDisplayImage() {
    if (images.empty()) {
        imageIndex = -1;
    }
    else {
        double ratio = ((double)ui->controlSlider->value())/100.0;
        ratio *= images.size();
        imageIndex = (int) ratio;
        imageIndex = (imageIndex == images.size()) ? imageIndex - 1 : imageIndex;
    }
}

VideoEditor::~VideoEditor() {
    delete ui;
}

