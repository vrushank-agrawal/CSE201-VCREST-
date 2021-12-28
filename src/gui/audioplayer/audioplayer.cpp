//
// Created by nhatv on 28 Dec 2021.
//

#include "audioplayer.h"

AudioPlayer::AudioPlayer() {
    player.setAudioOutput(&output);
}

AudioPlayer::~AudioPlayer() {

}

void AudioPlayer::seek(AudioItem *item, double time) {
    if (item->audioSource != source) {
        setSource(item->audioSource);
    }
    player.setPosition((time - item->start.key()) * 1000);
}


void AudioPlayer::setSource(QString source) {
    player.pause();
    player.setSource(QUrl(source));
    this->source = source;
    player.play();
    player.pause();
}

void AudioPlayer::updatePlayState(bool isPlaying) {
    this->isPlaying = isPlaying;
    if (isPlaying)
        player.play();
    else
        player.pause();
}

void AudioPlayer::handleIndicatorSignal(bool isPlaying) {
    if (isPlaying && this->isPlaying)
        player.play();
    else
        player.pause();
}
