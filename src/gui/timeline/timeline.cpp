//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#include <QDebug>
#include <QDateTime>
#include "timeline.h"
#include "sizegripitem.h"
#include "resizer.h"

double Timeline::default_image_length = 5;

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
    map = QMultiMap<double, Image*>();
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
    qDebug() << getImageAtIndicator();
}

void Timeline::addImage(Image *image, double start, double end) {
    auto *item = new ImageItem(image,
                                    map.insert(start, image),
                                    map.insert(end, nullptr),
                                    QPoint(start * xTimeOffset, ImageItem::border)
                                    );
    scene->addItem(item);

    qDebug() << map;
    connect(item, SIGNAL(itemMoved(ImageItem *, double, double)),
            this, SLOT(moveImageItem(ImageItem *, double, double)));
    connect(item, SIGNAL(positionChanged(ImageItem*, double, double)),
            this, SLOT(updateImagePosition(ImageItem*, double, double)));
    connect(item, SIGNAL(deleted(ImageItem *)),
            this, SLOT(deleteImage(ImageItem *)));

    item->createSizeGripItem(new SizeGripItem(new ImageItemResizer, item));
}

void Timeline::appendImage(Image *image, double length) {
    double start = map.isEmpty() ? 0 : map.lastKey();
    addImage(image, start, start + length);
}


void Timeline::updateImagePosition(ImageItem* item, double start, double end) {
    // delete old duration
    deleteImage(item);

    // add new duration
    item->start = map.insert(start, item->image);
    item->end = map.insert(end, nullptr);
    qDebug() << map;
}

Image* Timeline::getImage(double time) {
    QMultiMap<double, Image*>::iterator iterator = map.lowerBound(time);
    // find the greatest key smaller than this key
    if (iterator.key() > time) {
        iterator--;
        iterator = map.find(iterator.key());
    }

    // ignore nullptr
    while (iterator != map.end() && iterator.key() <= time) {
        if (iterator.value() != nullptr)
            return iterator.value();
        iterator++;
    }
    return nullptr;
}

Image* Timeline::getImageAtIndicator() {
    double time = indicator->x() / xTimeOffset;
    return getImage(time);
}

void Timeline::deleteImage(ImageItem *item) {
    map.erase(item->start);
    map.erase(item->end);
    qDebug() << map;
}

void Timeline::addImageAtIndicator(Image *image, double max_length) {
    double time = indicator->x() / xTimeOffset;

    // image already exists
    if (getImage(time) != nullptr) {
        appendImage(image, max_length);
        return;
    }

    QMultiMap<double, Image*>::iterator end = map.upperBound(time);
    double duration;
    if (end == map.end()) // trying to append image at the end of timeline
        duration = max_length;
    else
        duration = (end.key() - time > max_length) ? max_length : end.key() - time;
    addImage(image, time, time + duration);
}

void Timeline::moveImageItem(ImageItem *item, double startPos, double endPos) {
    double startTime = startPos / xTimeOffset;
    double endTime = endPos / xTimeOffset;

    // detect collision with other images
    Image* s = getImage(startTime);
    if (s != nullptr && s != item->image) return;
    QMultiMap<double, Image*>::iterator iterator = map.lowerBound(startTime);
    while (iterator != map.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item->image)
            return;
        iterator++;
    }

    item->setX(startPos);
}
