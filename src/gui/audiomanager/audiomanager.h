//
// Created by nhatv on 25 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_AUDIOMANAGER_H
#define VIDEO_EDITOR_BX23_AUDIOMANAGER_H


#include <QListWidget>

class AudioManager {
public:
    explicit AudioManager(QListWidget *qListWidget);
    ~AudioManager();
    void addAudio(QString name);

private:
    QListWidget *listWidget;
};


#endif //VIDEO_EDITOR_BX23_AUDIOMANAGER_H
