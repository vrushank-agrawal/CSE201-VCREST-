//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#include <QDebug>
#include <QDateTime>
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
    connect(indicator, SIGNAL(positionChanged(qreal)),
            this, SLOT(updateTime(qreal)));

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

    ImageItem::yOffset = timeHeight;
    ImageItem::xTimeOffset = xTimeOffset;
    map = QMap<double, Image*>();
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
    if (indicator->x() != time * xTimeOffset) {
        indicator->setPos(time * xTimeOffset, 0);
        moveTimeline();
        emit timeIndicatorChanged(time);
    }
}

void Timeline::updateTime(qreal xPosition) {
    double time = xPosition / xTimeOffset;
    emit timeIndicatorChanged(time);
}

void Timeline::addImage(Image *image, QPointF duration) {
    ImageItem *item = new ImageItem(image,
                                    duration,
                                    QPoint(duration.x() * xTimeOffset, ImageItem::border)
                                    );
    scene->addItem(item);

    QMap<double, Image*>::iterator xloc = map.find(duration.x());
    if (xloc != map.end() && xloc.value() == nullptr)
        map.remove(duration.x());

    map.insert(duration.x(), image);
    if (map.find(duration.y()) == map.end())
        map.insert(duration.y(), nullptr);
    qDebug() << "Current map:" << map;
    connect(item, SIGNAL(positionChanged(QPointF, QPointF)),
            this, SLOT(updateImagePosition(QPointF, QPointF)));
    connect(item, SIGNAL(deleted(ImageItem *)),
            this, SLOT(deleteImage(ImageItem *)));
}

void Timeline::appendImage(Image *image, double length) {
    double start = map.isEmpty() ? 0 : map.lastKey();
    addImage(image, QPointF(start, start + length));
}


void Timeline::updateImagePosition(QPointF prevDuration, QPointF newDuration) {
    QMap<double, Image*>::iterator iterator = map.find(prevDuration.x());
    if (iterator == map.end())
        return;

    Image *image = iterator.value();
    map.remove(prevDuration.x());
    map.insert(newDuration.x(), image);
    if (map.find(prevDuration.y()).value() == nullptr)
        map.remove(prevDuration.y());
    if (map.find(newDuration.y()) == map.end())
        map.insert(newDuration.y(), nullptr);
    qDebug() << map;
}

Image* Timeline::getImage(double time) {
    QMap<double, Image*>::iterator iterator = map.lowerBound(time);
    if (iterator == map.end())
        return nullptr;

    if (iterator.key() <= time)
        return iterator.value();
    else
        return nullptr;
}

void Timeline::deleteImage(ImageItem *item) {
    map.remove(item->duration.x());
    if (map.find(item->duration.y()).value() == nullptr)
        map.remove(item->duration.y());
}