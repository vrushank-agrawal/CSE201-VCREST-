//
// Created by nhatv on 2 Jan 2022.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"

void VideoEditor::appendAudioToThumbnail(QListWidgetItem *item) {
    QString *source = audioManager->getAudio(item);
    QMediaPlayer *player = audioManager->getPlayer(*source);
    ui->timeline->addAudioAtIndicator(*source, player->duration());
}