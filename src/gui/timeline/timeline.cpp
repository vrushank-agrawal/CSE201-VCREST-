//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#include <QDebug>
#include <QDateTime>
#include <cmath>
#include "timeline.h"

Timeline::Timeline(QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    sceneWidth = lengthInSecond * xTimeOffset;
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);

    indicator = new Indicator(sceneHeight);
    scene->addItem(indicator);
    indicator->setPos(0, 0);
    indicator->setZValue(101);
    indicator->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

    QLineF separator(0, 0, sceneWidth, 0);
    for (int i = 0; i < 2; i++) {
        QGraphicsItem *line = scene->addLine(separator);
        line->setPos(0, timeHeight + i * (sceneHeight - timeHeight) / 2);
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
        sceneWidth = lengthInSecond * xTimeOffset;
        scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
        emit videoLengthChanged(length);
    }
}

void Timeline::moveTimeline() {
    qreal xPosition = indicator->x() - sceneShowingWidth / 2;
    if (xPosition < 0) xPosition = 0;
    if (xPosition + sceneShowingWidth > sceneWidth) xPosition = sceneWidth - sceneShowingWidth;
    
    fitInView(xPosition, 0, sceneShowingWidth, sceneHeight + 10, Qt::IgnoreAspectRatio);
}

void Timeline::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    moveTimeline();
}

void Timeline::updateIndicatorPosition(double time) {
    indicator->setPos(time * xTimeOffset, 0);
    moveTimeline();
}