//
// Created by nhatv on 11 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoEditor.h" resolved

#include "videoeditor.h"
#include "ui_VideoEditor.h"
#include "imglist/imglist.h"
#include <QFileDialog>
#include <QMessageBox>


VideoEditor::VideoEditor(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::VideoEditor) {
    ui->setupUi(this);
          
    // add graphics view to preview
    ui->preview->setGraphicsView(ui->graphicsView);
//    ui->preview->play();
          
    connect(ui->importButton,  &QPushButton::clicked, this, &VideoEditor::importImage);
    connect(ui->controlSlider, &QSlider::valueChanged, this, &VideoEditor::setDisplayImage);
}

void VideoEditor::importImage() {
    QString filter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    QString fileName = QFileDialog::getOpenFileName(this, "Import image", "./", filter);
    if (fileName != "") {
        QMessageBox::information(this, "..", fileName);
    }
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

void VideoEditor::setupWidgets() {
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

