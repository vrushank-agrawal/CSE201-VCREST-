//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#include "timeline.h"
#include <QDebug>
#include <QDateTime>

Timeline::Timeline(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    width = lengthInSecond * xTimeOffset;
    scene->setSceneRect(0, 0, width, height);

    QLineF separator(0, 0, width, 0);
    for (int i = 0; i < 2; i++) {
        QGraphicsItem *line = scene->addLine(separator);
        line->setPos(0, timeHeight + i * (height - timeHeight) / 2);
        line->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    }

    QLineF timestamp(0, 0, 0, 10);

    for (int i = 0; i <= lengthInSecond; i += 5){
        QGraphicsItem *item = scene->addText(QDateTime::fromSecsSinceEpoch(i).toUTC().toString("hh:mm:ss"));
        item->setPos(i*xTimeOffset,yTime);
        item->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

        QGraphicsItem *line = scene->addLine(timestamp);
        line->setPos(i*xTimeOffset,yTime);
        line->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    }
}

Timeline::~Timeline() {
    delete scene;
}

void Timeline::updateVideoLength(int length) {
    if (lengthInSecond != length) {
        lengthInSecond = length;
        width = lengthInSecond * xTimeOffset;
        scene->setSceneRect(0, 0, width, height);
        emit videoLengthChanged(length);
    }
}

void Timeline::resizeEvent(QResizeEvent *event) {
    fitInView(0, 0, 3000, height+10, Qt::IgnoreAspectRatio);
    QGraphicsView::resizeEvent(event);
}