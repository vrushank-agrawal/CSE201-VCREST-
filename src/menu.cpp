//
// Created by nhatv on 09-Jan-22.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"

void VideoEditor::setupMenus() {
    // Files
    setupImports();
    ui->actionImport_Media->setShortcut(QKeySequence::Open);

    connect(ui->actionExport, &QAction::triggered,
            this, &VideoEditor::writeVideo);
    ui->actionExport->setShortcut(QKeySequence::Save);

    connect(ui->actionExit, &QAction::triggered,
            QApplication::quit);
    ui->actionExit->setShortcut(QKeySequence::Quit);


    // Image
    connect(ui->actionBlur_Image, &QAction::triggered,
            this, &VideoEditor::blurImage);
    connect(ui->actionBrighten_Image, &QAction::triggered,
            this, &VideoEditor::brightImage);
    connect(ui->actionRotate_Image, &QAction::triggered,
            this, &VideoEditor::rotateImageRight);
    connect(ui->actionReset_Image, &QAction::triggered,
            this, &VideoEditor::resetImage);


    // Preview
    connect(ui->actionPlay, &QAction::triggered,
            ui->preview, &VideoPlayer::play);
    ui->actionPlay->setShortcut(QKeySequence(Qt::Key_Space));

    connect(ui->actionPlay_from_Beginning, &QAction::triggered,
            this, &VideoEditor::playFromBeginning);
    ui->actionPlay_from_Beginning->setShortcut(QKeySequence::MoveToStartOfLine);

    connect(ui->actionForward, &QAction::triggered,
            ui->preview, &VideoPlayer::forward);
    ui->actionForward->setShortcut(QKeySequence::MoveToNextChar);

    connect(ui->actionBackward, &QAction::triggered,
            ui->preview, &VideoPlayer::backward);
    ui->actionBackward->setShortcut(QKeySequence::MoveToPreviousChar);
}

void VideoEditor::playFromBeginning() {
    updateCurrentTime(0);
}

void VideoEditor::quit() {
    QApplication::quit();
}