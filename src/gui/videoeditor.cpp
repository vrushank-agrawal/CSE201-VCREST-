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
    connect(ui->ImportButton,  &QPushButton::clicked, this, &VideoEditor::importImage);
}

//void MainWindow::loadImage(const QString &fileName)
//{
//    QPixmap newImage;
//    if (!newImage.load(fileName)) {
//        QMessageBox::warning(this, tr("Open Image"),
//                             tr("The image file could not be loaded."),
//                             QMessageBox::Close);
//        return;
//    }
//    puzzleImage = newImage;
//    setupPuzzle();
//}

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

VideoEditor::~VideoEditor() {
    delete ui;
}

