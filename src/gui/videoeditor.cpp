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
    connect(ui->importButton,  &QPushButton::clicked, this, &VideoEditor::ImportImage);
    connect(ui->controlSlider, &QSlider::valueChanged, this, &VideoEditor::SetAudioTimeSpan);
}

void VideoEditor::ImportImage() {
    QString filter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    QString fileName = QFileDialog::getOpenFileName(this, "Import image", "./", filter);
    if (fileName != "") {
        QMessageBox::information(this,"..",fileName);
    }
}

void VideoEditor::SetAudioTimeSpan() {
    audioTimeSpan = ((double)ui->controlSlider->value())/100.0;
    audioTimeSpan *= audioLength;
    audioTimeSpan = Round2Decimal(audioTimeSpan);
}

VideoEditor::~VideoEditor() {
    delete ui;
}

