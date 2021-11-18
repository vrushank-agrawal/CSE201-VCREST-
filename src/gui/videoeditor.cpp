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
    connect(ui->ImportButton,  &QPushButton::clicked, this, &VideoEditor::ImportImage);
}

void VideoEditor::ImportImage() {
    QString Filter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    QString FileName = QFileDialog::getOpenFileName(this, "Import image", "./", Filter);
    if (FileName != "") {
        QMessageBox::information(this,"..",FileName);
    }
}

VideoEditor::~VideoEditor() {
    delete ui;
}

