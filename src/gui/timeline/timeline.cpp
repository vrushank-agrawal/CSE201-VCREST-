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
    map = QMultiMap<double, ImageItem*>();
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

void Timeline::moveTimeline(TimelineMoveOption option = KeepCurrentPosition) {
    if (option == CenterIndicator) {
        currentXPosition = indicator->x() - sceneShowingWidth / 2;
        if (currentXPosition < 0) currentXPosition = 0;
        if (currentXPosition + sceneShowingWidth > sceneWidth) currentXPosition = sceneWidth - sceneShowingWidth;
    }

    fitInView(currentXPosition, 0, sceneShowingWidth, sceneHeight + 10, Qt::IgnoreAspectRatio);
    ImageItem::parentTransform = transform();
}

void Timeline::resizeEvent(QResizeEvent *event) {
    moveTimeline();
}

void Timeline::updateIndicatorPosition(double time) {
    if (indicator->x() != time * xTimeOffset) {
        indicator->setPos(time * xTimeOffset, 0);
        moveTimeline(CenterIndicator);
        emit timeIndicatorChanged(time);
    }
}

void Timeline::updateTime(qreal xPosition) {
    double time = xPosition / xTimeOffset;
    emit timeIndicatorChanged(time);
}

void Timeline::addImage(img::Image *image, double start, double end) {
    auto *item = new ImageItem(image, QPoint(start * xTimeOffset, ImageItem::border));
    item->start = map.insert(start, item);
    item->end = map.insert(end, nullptr);
    item->calculateSize();
    scene->addItem(item);

    connect(item, SIGNAL(itemMoved(ImageItem *, double, double)),
            this, SLOT(moveImageItem(ImageItem *, double, double)));
    connect(item, SIGNAL(positionChanged(ImageItem*, double, double)),
            this, SLOT(updateImagePosition(ImageItem*, double, double)));
    connect(item, SIGNAL(resized(ImageItem *, double)),
            this, SLOT(resizeImageItem(ImageItem *, double)));
    connect(item, SIGNAL(deleted(ImageItem *)),
            this, SLOT(deleteImage(ImageItem *)));

    item->createSizeGripItem(new SizeGripItem(new ImageItemResizer, item));

    emit imageAdded(image, start, end-start);
}

void Timeline::appendImage(img::Image *image, double length) {
    double start = map.isEmpty() ? 0 : map.lastKey();
    addImage(image, start, start + length);
}


void Timeline::updateImagePosition(ImageItem* item, double start, double end) {
    // delete old duration
    deleteImage(item);

    // add new duration
    item->start = map.insert(start, item);
    item->end = map.insert(end, nullptr);
    emit imageAdded(item->image, start, end-start);
}


ImageItem* Timeline::getImageItem(double time) {
    QMultiMap<double, ImageItem*>::iterator iterator = map.upperBound(time);

    // find the greatest key smaller than this key
    if (iterator == map.begin()) return nullptr;
    iterator--;
    iterator = map.find(iterator.key());

    // ignore nullptr
    while (iterator != map.end() && iterator.key() <= time) {
        if (iterator.value() != nullptr)
            return iterator.value();
        iterator++;
    }
    return nullptr;
}

img::Image* Timeline::getImage(double time) {
    ImageItem *item = getImageItem(time);
    if (item != nullptr) return item->image;
    return nullptr;
}

void Timeline::deleteImage(ImageItem *item) {
    map.erase(item->start);
    map.erase(item->end);
    emit imageDeleted(item->image);
}

void Timeline::addImageAtIndicator(img::Image *image, double max_length) {
    double time = indicator->x() / xTimeOffset;

    // image already exists
    if (getImage(time) != nullptr) {
        appendImage(image, max_length);
        return;
    }

    QMultiMap<double, ImageItem*>::iterator end = map.upperBound(time);
    double duration;
    if (end == map.end()) // trying to append image at the end of timeline
        duration = max_length;
    else
        duration = (end.key() - time > max_length) ? max_length : end.key() - time;
    addImage(image, time, time + duration);
}

void Timeline::setItemPosition(ImageItem *item, double startTime, double endTime) {
    ImageItem* s = getImageItem(startTime);
    if (s != nullptr && s != item) return;
    if (startTime < 0) return;
    QMultiMap<double, ImageItem*>::iterator iterator = map.lowerBound(startTime);
    while (iterator != map.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            return;
        }
        iterator++;
    }
    item->setX(startTime * xTimeOffset);
}

void Timeline::moveImageItem(ImageItem *item, double startPos, double endPos) {
    double startTime = startPos / xTimeOffset;
    double endTime = endPos / xTimeOffset;

    // detect collision with other images
    QMultiMap<double, ImageItem*>::iterator iterator = map.lowerBound(startTime);
    while (iterator != map.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            setItemPosition(item, startTime + iterator.key() - endTime, iterator.key());
            return;
        }
        iterator++;
    }

    setItemPosition(item, startTime, endTime);
}

void Timeline::resizeImageItem(ImageItem *item, double newLength) {
    double startTime = item->x() / xTimeOffset;
    double endTime = (item->x() + newLength) / xTimeOffset;

    // detect collision with other images
    QMultiMap<double, ImageItem*>::iterator iterator = map.lowerBound(startTime);
    while (iterator != map.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            emit imageDeleted(item->image);
            item->updateDuration((iterator.key() - startTime) * xTimeOffset);
            emit imageAdded(item->image, startTime, iterator.key() - startTime);
            return;
        }
        iterator++;
    }
    emit imageDeleted(item->image);
    item->updateDuration(newLength);
    emit imageAdded(item->image, startTime, newLength / xTimeOffset);
}

void Timeline::wheelEvent(QWheelEvent *event) {
    QPointF visible_left_point = mapToScene(0, 0);
    currentXPosition = visible_left_point.x();
    QGraphicsView::wheelEvent(event);
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