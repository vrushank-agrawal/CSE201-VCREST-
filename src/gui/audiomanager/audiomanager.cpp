//
// Created by nhatv on 25 Nov 2021.
//

#include "audiomanager.h"

AudioManager::AudioManager(QListWidget *qListWidget) : listWidget(qListWidget){
    qListWidget->setDragEnabled(true);
    qListWidget->setViewMode(QListView::ListMode);
//    qListWidget->setIconSize(QSize(50, 50));
//    qListWidget->setGridSize(QSize(80, 90));
//    qListWidget->setSpacing(20);
//    qListWidget->setContentsMargins(20, 20, 20, 20);
    qListWidget->setMovement(QListView::Snap);
    qListWidget->setAcceptDrops(true);
    qListWidget->setDropIndicatorShown(true);
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