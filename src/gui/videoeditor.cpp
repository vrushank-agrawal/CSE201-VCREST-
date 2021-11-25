//
// Created by nhatv on 11 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoEditor.h" resolved

#include "videoeditor.h"
#include "ui_VideoEditor.h"
#include "imagethumbnail/imagethumbnail.h"
#include <QFileDialog>
#include <QMessageBox>


VideoEditor::VideoEditor(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::VideoEditor) {
    ui->setupUi(this);
          
    // add graphics view to preview
    ui->preview->setChild(ui->label, ui->playButton);
    ui->preview->updateVideo(cv::VideoCapture("link to the video"));

    setupMenus();
    setupWidgets();

    connect(ui->controlSlider, &QSlider::valueChanged, this, &VideoEditor::setDisplayImage);
}

void VideoEditor::setupMenus() {
    ui->actionImport_Media->setShortcut(QKeySequence::Open);
    connect(ui->actionImport_Media, &QAction::triggered, this, &VideoEditor::importMedia);
}

void VideoEditor::setupWidgets() {
    setupImageListWidget();
}

void VideoEditor::importMedia() {
    QString fileName = importImage();
    loadImage(fileName);
}

QString VideoEditor::importImage() {
    QString filter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    QString fileName = QFileDialog::getOpenFileName(this, "Import image", "./", filter);
    if (fileName != "") {
        QMessageBox::information(this, "..", fileName);
    }
    return fileName;
}

void VideoEditor::loadImage(const QString &path) {
    QPixmap img;
    if (!img.load(path)) {
        QMessageBox::warning(this, tr("Open Image"),
                             tr("The image file could not be loaded"),
                             QMessageBox::Close);
        return;
    }
}

void VideoEditor::setupImageListWidget() {
    thumbnailManager = new ThumbnailManager(ui->imgListWidget);

    auto *testPixmap = new QPixmap(":/img-error.png");
    auto *brush = new QBrush(Qt::white);

    thumbnailManager->addImage(*testPixmap, "test1");
    thumbnailManager->addImage(*testPixmap, "test2");
    thumbnailManager->addImage(*testPixmap, "test2222222222222222222222222222222222222222222");
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

