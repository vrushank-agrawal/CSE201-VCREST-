//
// Created by nhatv on 25 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_AUDIOMANAGER_H
#define VIDEO_EDITOR_BX23_AUDIOMANAGER_H


#include <QListWidget>
#include <QMediaPlayer>
#include "Audio.hpp"

class AudioManager : public QObject {
Q_OBJECT

public:
    explicit AudioManager(QListWidget *qListWidget);
    ~AudioManager();
    void addAudio(const QString& name);
    audio::Audio* getAudio(QListWidgetItem *item);
    QMediaPlayer* getPlayer(audio::Audio* audio);

private:
    QListWidget *listWidget = nullptr;
    QMap<QListWidgetItem*, audio::Audio*> map;
    QMap<audio::Audio*, QMediaPlayer*> playerMap;
};


#endif //VIDEO_EDITOR_BX23_AUDIOMANAGER_H
