//
// Created by nhatv on 28 Dec 2021.
//

#ifndef VIDEO_EDITOR_BX23_AUDIOPLAYER_H
#define VIDEO_EDITOR_BX23_AUDIOPLAYER_H


#include <QMediaPlayer>
#include <QAudioOutput>

class AudioPlayer : public QObject {
Q_OBJECT

public:
    explicit AudioPlayer();
    ~AudioPlayer();

    void seek(double relativeTime);
    void setSource(QString source);


public slots:
    void updatePlayState(bool isPlaying);


private:
    QMediaPlayer player;
    QAudioOutput output;
};


#endif //VIDEO_EDITOR_BX23_AUDIOPLAYER_H
