//
// Created by nhatv on 28 Dec 2021.
//

#include "audioplayer.h"
#include <QTimer>

AudioPlayer::AudioPlayer(AudioManager* manager, Timeline* timeline) : manager(manager), timeline(timeline){
}

AudioPlayer::~AudioPlayer() {

}

void AudioPlayer::seek(AudioItem *item, double time) {
//    if (item == nullptr) {
//        setSource("");
//        return;
//    }
//    if (item->audioSource != source) {
//        setSource(item->audioSource);
//    }
//    player.setPosition((time - item->start.key()) * 1000);
}


void AudioPlayer::setSource(QString source) {
//    player.pause();
//    player.setSource(QUrl(source));
//    this->source = source;
//    if (!player.isSeekable()) {
//        player.play();
//        QTimer::singleShot(20, this, &AudioPlayer::initAudioSource);
//    } else
//        updatePlayState(isPlaying);
}


void AudioPlayer::initAudioSource() {
//    player.pause();
//    qDebug() << "Initializing Audio Source..." <<  player.isSeekable();
//    if (player.isSeekable()) {
//        player.setPosition(0);
//    }
//    updatePlayState(isPlaying);
}


void AudioPlayer::updatePlayState(bool isPlaying) {
    this->isPlaying = isPlaying;
    if (player == nullptr) return;
    if (isPlaying) {
        qDebug() << "playing" << player->position() << player->isSeekable();
        player->play();
    }
    else
        player->pause();
}

void AudioPlayer::handleIndicatorSignal(bool isSuspending) {
    if (player == nullptr) return;
    this->isSuspending = isSuspending;
    if (isSuspending && isPlaying)
        player->play();
    else
        player->pause();
}

void AudioPlayer::seek(double time) {
    AudioItem *item = timeline->getAudioItem(time);
    if (item == nullptr) {
        qDebug() << "no audio";
        if (player != nullptr) player->pause();
        player = nullptr;
        return;
    }
    qDebug() << item->audioSource;
    QMediaPlayer *newPlayer = manager->getPlayer(item->audioSource);
    if (newPlayer != player) {
        qDebug() << "switching player";
        if (player != nullptr)
            player->pause();
        player = newPlayer;
        updatePlayState(isPlaying);
    }
    double start = timeline->getAudioStartTime(time);

    if (player != nullptr)
        player->setPosition((time - start) * 1000);
}