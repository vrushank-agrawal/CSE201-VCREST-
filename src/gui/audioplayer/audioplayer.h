//
// Created by nhatv on 28 Dec 2021.
//

#ifndef VIDEO_EDITOR_BX23_AUDIOPLAYER_H
#define VIDEO_EDITOR_BX23_AUDIOPLAYER_H


#include <QMediaPlayer>
#include <QAudioOutput>
#include <audioitem.h>
#include <audiomanager.h>
#include <timeline.h>

class AudioPlayer : public QObject {
Q_OBJECT

public:
    explicit AudioPlayer(AudioManager* manager, Timeline* timeline);
    ~AudioPlayer();


public slots:
    void handleIndicatorSignal(bool isSuspending);
    void seek(double time);
    void updatePlayState(bool isPlaying);


private:
    bool isPlaying = false;
    bool isSuspending = false;
    QString source = "";
    AudioItem *currentItem;
    AudioManager *manager;
    QMediaPlayer *player;
    Timeline *timeline;
};


#endif //VIDEO_EDITOR_BX23_AUDIOPLAYER_H
