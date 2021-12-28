//
// Created by nhatv on 28 Dec 2021.
//

#ifndef VIDEO_EDITOR_BX23_AUDIOPLAYER_H
#define VIDEO_EDITOR_BX23_AUDIOPLAYER_H


#include <QMediaPlayer>
#include <QAudioOutput>
#include "audioitem.h"

class AudioPlayer : public QObject {
Q_OBJECT

public:
    explicit AudioPlayer();
    ~AudioPlayer();

    void seek(AudioItem *source, double time);
    void setSource(QString source);


public slots:
    void handleIndicatorSignal(bool isPlaying);
    void updatePlayState(bool isPlaying);


private:
    bool isPlaying = false;
    QMediaPlayer player;
    QAudioOutput output;
    QString source = "";
};


#endif //VIDEO_EDITOR_BX23_AUDIOPLAYER_H
