//
// Created by nhatv on 25 Nov 2021.
//

#include "audiomanager.h"
#include "QAudioOutput"
#include <QTimer>

AudioManager::AudioManager(QListWidget *qListWidget) : listWidget(qListWidget){
    qListWidget->setDragEnabled(true);
    qListWidget->setViewMode(QListView::ListMode);
    qListWidget->setIconSize(QSize(20, 20));
    qListWidget->setMovement(QListView::Snap);
    qListWidget->setAcceptDrops(false);
    qListWidget->setDropIndicatorShown(true);
    qListWidget->setDefaultDropAction(Qt::MoveAction);
    qListWidget->setWordWrap(true);
    qListWidget->setUniformItemSizes(true);
    qListWidget->setAutoScrollMargin(100);
}

void AudioManager::addAudio(const QString& name) {
    auto *item = new QListWidgetItem(QIcon(QPixmap(":/file-mp3.png")), name);
    item->setSizeHint(QSize(60, 70));
    listWidget->addItem(item);
    map.insert(item, name);

    auto *player = new QMediaPlayer;
    player->setAudioOutput(new QAudioOutput);
    player->setSource(QUrl(name));
    playerMap.insert(name, player);

    player->play();
    connect(player, SIGNAL(seekableChanged(bool)),
            player, SLOT(pause()));
}

AudioManager::~AudioManager() {
    delete listWidget;
    for (auto &player: playerMap) {
        delete player->audioOutput();
        delete player;
    }
}

QString *AudioManager::getAudio(QListWidgetItem *item) {
    return &map.find(item).value();
}

QMediaPlayer *AudioManager::getPlayer(QString source) {
    return playerMap.value(source, nullptr);
}
