//
// Created by nhatv on 09-Jan-22.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"

void VideoEditor::setupMenus() {
    setupImports();
    connect(ui->actionExport, &QAction::triggered,
            this, &VideoEditor::writeVideo);
    connect(ui->actionBlur_Image, &QAction::triggered,
            this, &VideoEditor::blurImage);
    connect(ui->actionBrighten_Image, &QAction::triggered,
            this, &VideoEditor::brightImage);
    connect(ui->actionRotate_Image, &QAction::triggered,
            this, &VideoEditor::rotateImageRight);
    connect(ui->actionReset_Image, &QAction::triggered,
            this, &VideoEditor::resetImage);
    connect(ui->actionPlay, &QAction::triggered,
            ui->preview, &VideoPlayer::play);
    connect(ui->actionPlay_from_Beginning, &QAction::triggered,
            this, &VideoEditor::playFromBeginning);
}

void VideoEditor::playFromBeginning() {
    updateCurrentTime(0);
}