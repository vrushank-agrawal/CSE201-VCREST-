//
// Created by nhatv on 25 Nov 2021.
//

#include "audiomanager.h"

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

void AudioManager::addAudio(QString name) {
    auto *item = new QListWidgetItem(QIcon(QPixmap(":/file-mp3.png")), name);
    listWidget->addItem(item);
}

AudioManager::~AudioManager() {
    delete listWidget;
}