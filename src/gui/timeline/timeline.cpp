//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#include <QDebug>
#include <QDateTime>
#include <audioresizer.h>
#include <imageresizer.h>
#include "timeline.h"
#include "sizegripitem.h"

/*###################
 *      GENERIC
 ####################*/

double Timeline::default_audio_length = 5;
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
    AudioItem::yOffset = (timeHeight + sceneHeight) / 2;
    ImageItem::xTimeOffset = xTimeOffset;
    imageMap = QMultiMap<double, ImageItem*>();
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
}

void Timeline::resizeEvent(QResizeEvent *event) {
    moveTimeline();
}

void Timeline::updateIndicatorPosition(double time) {
    if (indicator->x() != time * xTimeOffset) {
        indicator->setPos(time * xTimeOffset, 0);
        moveTimeline(CenterIndicator);
        emit timeIndicatorChanged(time);
        qDebug() << getAudio(time);
    }
}

void Timeline::updateTime(qreal xPosition) {
    double time = xPosition / xTimeOffset;
    emit timeIndicatorChanged(time);
}

void Timeline::wheelEvent(QWheelEvent *event) {
    QPointF visible_left_point = mapToScene(0, 0);
    currentXPosition = visible_left_point.x();
    QGraphicsView::wheelEvent(event);
}





/*###################
 *      AUDIO
 ####################*/

void Timeline::addAudio(QString audioSource, double start, double end) {
    auto *item = new AudioItem(audioSource, QPoint(start * xTimeOffset, AudioItem::border));
    qDebug() << audioSource << item->audioSource;
    item->start = audioMap.insert(start, item);
    item->end = audioMap.insert(end, nullptr);
    item->calculateSize();
    scene->addItem(item);

    connect(item, SIGNAL(itemMoved(AudioItem *, double, double)),
            this, SLOT(moveAudioItem(AudioItem *, double, double)));
    connect(item, SIGNAL(positionChanged(AudioItem*, double, double)),
            this, SLOT(updateAudioPosition(AudioItem*, double, double)));
    connect(item, SIGNAL(resized(AudioItem *, double)),
            this, SLOT(resizeAudioItem(AudioItem *, double)));
    connect(item, SIGNAL(deleted(AudioItem *)),
            this, SLOT(deleteAudio(AudioItem *)));

    item->createSizeGripItem(new SizeGripItem(new AudioItemResizer, item));
}

void Timeline::appendAudio(QString audioSource, double length) {
    double start = audioMap.isEmpty() ? 0 : audioMap.lastKey();
    addAudio(audioSource, start, start + length);
}

void Timeline::addAudioAtIndicator(QString audioSource, double max_length) {
    double time = indicator->x() / xTimeOffset;

    // image already exists
    if (getAudioItem(time) != nullptr) {
        appendAudio(audioSource, max_length);
        return;
    }

    QMultiMap<double, AudioItem*>::iterator end = audioMap.upperBound(time);
    double duration;
    if (end == audioMap.end()) // trying to append image at the end of timeline
        duration = max_length;
    else
        duration = (end.key() - time > max_length) ? max_length : end.key() - time;
    addAudio(audioSource, time, time + duration);
}

void Timeline::deleteAudio(AudioItem *item) {
    audioMap.erase(item->start);
    audioMap.erase(item->end);
    emit audioDeleted(item->audioSource);
}

QString Timeline::getAudio(qreal time) {
    AudioItem *item = getAudioItem(time);
    if (item != nullptr) return item->audioSource;
    return nullptr;
}

AudioItem* Timeline::getAudioItem(double time) {
    QMultiMap<double, AudioItem*>::iterator iterator = audioMap.upperBound(time);

    // find the greatest key smaller than this key
    if (iterator == audioMap.begin()) return nullptr;
    iterator--;
    iterator = audioMap.find(iterator.key());

    // ignore nullptr
    while (iterator != audioMap.end() && iterator.key() <= time) {
        if (iterator.value() != nullptr)
            return iterator.value();
        iterator++;
    }
    return nullptr;
}

void Timeline::moveAudioItem(AudioItem *item, double startPos, double endPos) {
    double startTime = startPos / xTimeOffset;
    double endTime = endPos / xTimeOffset;

    // detect collision with other images
    QMultiMap<double, AudioItem*>::iterator iterator = audioMap.lowerBound(startTime);
    while (iterator != audioMap.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            setAudioItemPosition(item, startTime + iterator.key() - endTime, iterator.key());
            return;
        }
        iterator++;
    }

    setAudioItemPosition(item, startTime, endTime);
}

void Timeline::resizeAudioItem(AudioItem *item, double newLength) {
    double startTime = item->x() / xTimeOffset;
    double endTime = (item->x() + newLength) / xTimeOffset;

    // detect collision with other audios
    QMultiMap<double, AudioItem*>::iterator iterator = audioMap.lowerBound(startTime);
    while (iterator != audioMap.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            item->updateDuration((iterator.key() - startTime) * xTimeOffset);
            return;
        }
        iterator++;
    }
    item->updateDuration(newLength);
}

void Timeline::setAudioItemPosition(AudioItem *item, double startTime, double endTime) {
    AudioItem* s = getAudioItem(startTime);
    if (s != nullptr && s != item) return;
    if (startTime < 0) return;
    QMultiMap<double, AudioItem*>::iterator iterator = audioMap.lowerBound(startTime);
    while (iterator != audioMap.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            return;
        }
        iterator++;
    }
    item->setX(startTime * xTimeOffset);
}

void Timeline::updateAudioPosition(AudioItem *item, double start, double end) {
    // delete old duration
    deleteAudio(item);

    // add new duration
    item->start = audioMap.insert(start, item);
    item->end = audioMap.insert(end, nullptr);
    emit audioAdded(item->audioSource, start, end-start);
}





/*###################
 *      IMAGE
 ####################*/

void Timeline::addImage(img::Image *image, double start, double end) {
    auto *item = new ImageItem(image, QPoint(start * xTimeOffset, ImageItem::border));
    item->start = imageMap.insert(start, item);
    item->end = imageMap.insert(end, nullptr);
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

    connect(item, &ImageItem::animationApplied,
            this, &Timeline::animationApplied);

    item->createSizeGripItem(new SizeGripItem(new ImageItemResizer, item));

    emit imageAdded(image, start, end-start, vid::Normal);
}

void Timeline::addImageAtIndicator(img::Image *image, double max_length) {
    double time = indicator->x() / xTimeOffset;

    // image already exists
    if (getImage(time) != nullptr) {
        appendImage(image, max_length);
        return;
    }

    QMultiMap<double, ImageItem*>::iterator end = imageMap.upperBound(time);
    double duration;
    if (end == imageMap.end()) // trying to append image at the end of timeline
        duration = max_length;
    else
        duration = (end.key() - time > max_length) ? max_length : end.key() - time;
    addImage(image, time, time + duration);
}

void Timeline::appendImage(img::Image *image, double length) {
    double start = imageMap.isEmpty() ? 0 : imageMap.lastKey();
    addImage(image, start, start + length);
}

void Timeline::deleteImage(ImageItem *item) {
    imageMap.erase(item->start);
    imageMap.erase(item->end);
    emit imageDeleted(item->image);
}

img::Image* Timeline::getImage(double time) {
    ImageItem *item = getImageItem(time);
    if (item != nullptr) return item->image;
    return nullptr;
}

ImageItem* Timeline::getImageItem(double time) {
    QMultiMap<double, ImageItem*>::iterator iterator = imageMap.upperBound(time);

    // find the greatest key smaller than this key
    if (iterator == imageMap.begin()) return nullptr;
    iterator--;
    iterator = imageMap.find(iterator.key());

    // ignore nullptr
    while (iterator != imageMap.end() && iterator.key() <= time) {
        if (iterator.value() != nullptr)
            return iterator.value();
        iterator++;
    }
    return nullptr;
}

void Timeline::moveImageItem(ImageItem *item, double startPos, double endPos) {
    double startTime = startPos / xTimeOffset;
    double endTime = endPos / xTimeOffset;

    // detect collision with other images
    QMultiMap<double, ImageItem*>::iterator iterator = imageMap.lowerBound(startTime);
    while (iterator != imageMap.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            setImageItemPosition(item, startTime + iterator.key() - endTime, iterator.key());
            return;
        }
        iterator++;
    }

    setImageItemPosition(item, startTime, endTime);
}

void Timeline::resizeImageItem(ImageItem *item, double newLength) {
    double startTime = item->x() / xTimeOffset;
    double endTime = (item->x() + newLength) / xTimeOffset;

    // detect collision with other images
    QMultiMap<double, ImageItem*>::iterator iterator = imageMap.lowerBound(startTime);
    while (iterator != imageMap.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            item->updateDuration((iterator.key() - startTime) * xTimeOffset);
            return;
        }
        iterator++;
    }
    item->updateDuration(newLength);
}

void Timeline::setImageItemPosition(ImageItem *item, double startTime, double endTime) {
    ImageItem* s = getImageItem(startTime);
    if (s != nullptr && s != item) return;
    if (startTime < 0) return;
    QMultiMap<double, ImageItem*>::iterator iterator = imageMap.lowerBound(startTime);
    while (iterator != imageMap.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            return;
        }
        iterator++;
    }
    item->setX(startTime * xTimeOffset);
}

void Timeline::updateImagePosition(ImageItem* item, double start, double end) {
    // delete old duration
    deleteImage(item);

    // add new duration
    item->start = imageMap.insert(start, item);
    item->end = imageMap.insert(end, nullptr);
    emit imageAdded(item->image, start, end-start, item->animation);
}
