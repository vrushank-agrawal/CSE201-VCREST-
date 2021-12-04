//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#include "timeline.h"
#include <QDebug>

Timeline::Timeline(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0, 0, lengthInSecond * xTimeOffset, 100);
    for (int i = 0; i < lengthInSecond; i++){
        QGraphicsItem *item = scene->addText(QString::number(i));
        item->setPos(i*xTimeOffset,yTime);
    }
    for (int i = 0; i < lengthInSecond; i++){
        QGraphicsItem *item = scene->addText(QString::number(i));
        item->setPos(i*xTimeOffset,yTime + 100);
    }
    qDebug() << scene->sceneRect() << " " << sceneRect() << "\n";
}

Timeline::~Timeline() {
    delete scene;
}

void Timeline::updateVideoLength(int length) {
    if (lengthInSecond != length) {
        lengthInSecond = length;
        scene->setSceneRect(0, 0, lengthInSecond * xTimeOffset, 100);
        emit videoLengthChanged(length);
    }
}

void Timeline::resizeEvent(QResizeEvent *event) {
    scale(1, event->size().height() / 150.0);
    qDebug() << transform() << '\n';
    QGraphicsView::resizeEvent(event);
}