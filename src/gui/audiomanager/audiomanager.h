//
// Created by nhatv on 25 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_AUDIOMANAGER_H
#define VIDEO_EDITOR_BX23_AUDIOMANAGER_H


#include <QListWidget>
#include <QMediaPlayer>

class AudioManager : public QObject {
Q_OBJECT

public:
    explicit AudioManager(QListWidget *qListWidget);
    ~AudioManager();
    void addAudio(const QString& name);
    QString* getAudio(QListWidgetItem *item);
    QMediaPlayer* getPlayer(QString source);

private:
    QListWidget *listWidget;
    QMap<QListWidgetItem*, QString> map;
    QMap<QString, QMediaPlayer*> playerMap;
};


#endif //VIDEO_EDITOR_BX23_AUDIOMANAGER_H
