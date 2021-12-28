//
// Created by nhatv on 28 Dec 2021.
//

#include "audioplayer.h"

AudioPlayer::AudioPlayer() {
    player.setAudioOutput(&output);
}

AudioPlayer::~AudioPlayer() {

}

void AudioPlayer::seek(double relativeTime) {
    player.setPosition(relativeTime * 1000);
}

void AudioPlayer::setSource(QString source) {
    player.pause();
    player.setSource(QUrl(source));
    player.play();
    player.pause();
}

void AudioPlayer::updatePlayState(bool isPlaying) {
    if (isPlaying)
        player.play();
    else
        player.pause();
}
