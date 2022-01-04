//
// Created by nhatv on 28 Dec 2021.
//

#include "audioplayer.h"
#include <QTimer>

AudioPlayer::AudioPlayer(AudioManager* manager, Timeline* timeline) : manager(manager), timeline(timeline){}

AudioPlayer::~AudioPlayer() {

}


void AudioPlayer::updatePlayState(bool isPlaying) {
    this->isPlaying = isPlaying;
    if (player == nullptr) return;
    if (isPlaying) {
        player->play();
    }
    else
        player->pause();
}

void AudioPlayer::handleIndicatorSignal(bool isSuspending) {
    this->isSuspending = isSuspending;
    if (player == nullptr) return;
    if (isSuspending && isPlaying)
        player->play();
    else
        player->pause();
}

void AudioPlayer::seek(double time) {
    AudioItem *item = timeline->getAudioItem(time);
    if (item == nullptr) {
        if (player != nullptr) player->pause();
        player = nullptr;
        return;
    }
    QMediaPlayer *newPlayer = manager->getPlayer(item->audio);
    if (newPlayer != player) {
        qDebug() << "switching player";
        if (player != nullptr)
            player->pause();
        player = newPlayer;
        updatePlayState(isPlaying);
    }
    double start = timeline->getAudioStartTime(time);

    if (player != nullptr && start >= 0)
        player->setPosition((time - start) * 1000);
}