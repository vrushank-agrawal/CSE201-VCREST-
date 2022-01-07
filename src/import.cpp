//
// Created by nhatv on 2 Jan 2022.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"
#include <QFileDialog>

void VideoEditor::importAudio(const QString& fileName) {
    audioManager->addAudio(fileName);
}

void VideoEditor::importAudios() {
    QStringList files = importFiles("Import Audios", "/", audioFileTypesFilter);
    for (auto & file : files) {
        if (audioFileTypes.contains(file.right(4))) {
            importAudio(file);
        }
    }
}

QStringList VideoEditor::importFiles(const QString &caption, const QString &dir, const QString &filter) {
    QStringList files = QFileDialog::getOpenFileNames(this, caption, dir, filter);
    return files;
}

void VideoEditor::importImage(const QString& fileName) {
    img::Image image(fileName.toStdString());
    imageManager->addImage(image, fileName);
}

void VideoEditor::importImages() {
    QStringList files = importFiles("Import Images", "/", imageFileTypesFilter);
    for (auto & file : files) {
        if (imageFileTypes.contains(file.right(4))) {
            importImage(file);
        }
    }
}

void VideoEditor::importMedia() {
    QStringList files = importFiles("Import Media", "/", mediaFileTypesFilter);

    for (auto & file : files) {
        if (imageFileTypes.contains(file.right(4))) {
            importImage(file);
        } else if (audioFileTypes.contains(file.right(4))) {
            importAudio(file);
        } else {
            qDebug() << "Invalid file:" << file;
        }
    }
}

void VideoEditor::setupImports() {
    imageFileTypes << ".jpg" << ".png" << ".gif" << ".svg";
    imageFileTypesFilter = "Images (*.jpg *.png *.gif *.svg)";
    audioFileTypes << ".wav" << ".mp3";
    audioFileTypesFilter = "Audio (*.wav *.mp3)";
    mediaFileTypes << ".jpg" << ".png" << ".gif" << ".svg" << ".wav" << ".mp3";
    mediaFileTypesFilter = "Media (*.jpg *.png *.gif *.svg *.wav *.mp3)";

    ui->actionImport_Media->setShortcut(QKeySequence::Open);
    ui->actionExport->setShortcut(QKeySequence::Save);
    connect(ui->actionImport_Image, SIGNAL(triggered(bool)),
            this, SLOT(importImages()));
    connect(ui->actionImport_Audio, SIGNAL(triggered(bool)),
            this, SLOT(importAudios()));
    connect(ui->actionImport_Media, SIGNAL(triggered(bool)),
            this, SLOT(importMedia()));
}