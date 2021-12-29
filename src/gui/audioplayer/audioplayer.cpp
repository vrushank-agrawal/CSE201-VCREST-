//
// Created by nhatv on 28 Dec 2021.
//

#include "audioplayer.h"
#include <QTimer>

AudioPlayer::AudioPlayer() {
    player.setAudioOutput(&output);
}

AudioPlayer::~AudioPlayer() {

}

void AudioPlayer::seek(AudioItem *item, double time) {
    if (item == nullptr) {
        setSource("");
        return;
    }
    if (item->audioSource != source) {
        setSource(item->audioSource);
    }
    player.setPosition((time - item->start.key()) * 1000);
}


void AudioPlayer::setSource(QString source) {
    player.pause();
    player.setSource(QUrl(source));
    this->source = source;
    if (!player.isSeekable()) {
        player.play();
        QTimer::singleShot(20, this, &AudioPlayer::initAudioSource);
    } else
        updatePlayState(isPlaying);
}


void AudioPlayer::initAudioSource() {
    player.pause();
    qDebug() << "Initializing Audio Source..." <<  player.isSeekable();
    if (player.isSeekable()) {
        player.setPosition(0);
    }
    updatePlayState(isPlaying);
}


void AudioPlayer::updatePlayState(bool isPlaying) {
    this->isPlaying = isPlaying;
    if (isPlaying) {
        qDebug() << "played";
        player.play();
    }
    else
        player.pause();
}

void AudioPlayer::handleIndicatorSignal(bool isSuspending) {
    this->isSuspending = isSuspending;
    if (isSuspending && isPlaying)
        player.play();
    else
        player.pause();
}
