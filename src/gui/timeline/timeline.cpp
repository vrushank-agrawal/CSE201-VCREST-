//
// Created by Minh Tung Nguyen on 03/12/2021.
//


#include <QDateTime>
#include <audioresizer.h>
#include <imageresizer.h>
#include "timeline.h"
#include "sizegripitem.h"

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
    connect(indicator, SIGNAL(positionChanged(qreal)),
            this, SLOT(updateTime(qreal)));
    connect(indicator, SIGNAL(playStateChanged(bool)),
            this, SLOT(relayPlayStateChanged(bool)));

    QPen pen("#bbbbbb");
    QLineF separator(0, 0, sceneWidth, 0);
    for (int i = 0; i < 2; i++) {
        QGraphicsItem *line = scene->addLine(separator, pen);
        line->setPos(0, timeHeight + i * (sceneHeight - timeHeight) / 2);
        line->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    }

    QLineF timestamp(0, 0, 0, 10);

    for (int i = 0; i <= lengthInSecond; i += 5){
        QGraphicsTextItem *item = scene->addText(QDateTime::fromSecsSinceEpoch(i).toUTC().toString("hh:mm:ss"));
        item->setDefaultTextColor("#bbbbbb");
        item->setPos(i*xTimeOffset,yTime);
        item->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

        QGraphicsItem *line = scene->addLine(timestamp, pen);
        line->setPos(i*xTimeOffset,yTime);
        line->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    }


    ImageItem::yOffset = timeHeight;
    ImageItem::xTimeOffset = xTimeOffset;
    AudioItem::yOffset = (timeHeight + sceneHeight) / 2;
    ImageItem::xTimeOffset = xTimeOffset;
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

void Timeline::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF pos = mapToScene(event->pos());
        if (timeHeight <= pos.y() && pos.y() <= sceneHeight) {
            ImageItem::setSelectedImageItem();
            emit imageSelected();
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void Timeline::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF pos = mapToScene(event->pos());
        if (pos.y() < timeHeight) {
            indicator->setX(pos.x());
            updateTime(pos.x());
        }
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void Timeline::moveTimeline(TimelineMoveOption option = KeepCurrentPosition) {
    if (option == CenterIndicator) {
        currentXPosition = indicator->x() - sceneShowingWidth / 2;
        if (currentXPosition < 0) currentXPosition = 0;
        if (currentXPosition + sceneShowingWidth > sceneWidth) currentXPosition = sceneWidth - sceneShowingWidth;
    }

    fitInView(currentXPosition, 0, sceneShowingWidth, sceneHeight + 10, Qt::IgnoreAspectRatio);
    ImageItem::parentTransform = transform();
    AudioItem::parentTransform = transform();
}

void Timeline::relayPlayStateChanged(bool isPlaying) {
    emit playStateChanged(isPlaying);
}

void Timeline::resizeEvent(QResizeEvent *event) {
    moveTimeline();
}

void Timeline::updateIndicatorPosition(double time) {
    if (indicator->x() != time * xTimeOffset) {
        indicator->setPos(time * xTimeOffset, 0);
        moveTimeline(CenterIndicator);
        emit timeIndicatorChanged(time);

        QMultiMap<double, AudioItem*>::iterator iterator = audioMap.upperBound(time);
        // find the greatest key smaller than this key
        if (iterator != audioMap.begin()) {
            iterator--;
        }
        if (time - iterator.key() >= 0 && time - iterator.key() <= 0.1) {
            emit seekAudioRequested(time);
        }
    }
}

void Timeline::updateTime(qreal xPosition) {
    double time = xPosition / xTimeOffset;
    emit timeIndicatorChanged(time);
    emit seekAudioRequested(time);
}

void Timeline::wheelEvent(QWheelEvent *event) {
    QPointF visible_left_point = mapToScene(0, 0);
    currentXPosition = visible_left_point.x();
    QGraphicsView::wheelEvent(event);
}