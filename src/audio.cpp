//
// Created by nhatv on 2 Jan 2022.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"

void VideoEditor::appendAudioToThumbnail(QListWidgetItem *item) {
    audio::Audio *source = audioManager->getAudio(item);
    QMediaPlayer *player = audioManager->getPlayer(source);
    ui->timeline->addAudioAtIndicator(source, item->text(), player->duration());
}