//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#include "timeline.h"
#include <QDebug>

Timeline::Timeline(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    for (int i = 0; i < lengthInSecond; i++){
        QGraphicsItem *item = scene->addText(QString::number(i));
        item->setPos(i*xTimeOffset,yTime);
    }
    for (int i = 0; i < lengthInSecond; i++){
        QGraphicsItem *item = scene->addText(QString::number(i));
        item->setPos(i*xTimeOffset,yTime + 100);
    }
}

Timeline::~Timeline() {
    delete scene;
}