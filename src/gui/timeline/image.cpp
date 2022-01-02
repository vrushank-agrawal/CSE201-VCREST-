//
// Created by nhatv on 2 Jan 2022.
//

#include "imageresizer.h"
#include "timeline.h"

double Timeline::default_image_length = 5;

void Timeline::addImage(img::Image *image, double start, double end) {
    auto *item = new ImageItem(image, QPoint(start * xTimeOffset, ImageItem::border));
    item->start = imageMap.insert(start, item);
    item->end = imageMap.insert(end, nullptr);
    item->calculateSize();
    scene->addItem(item);

    connect(item, SIGNAL(itemMoved(ImageItem*,double,double)),
            this, SLOT(moveImageItem(ImageItem*,double,double)));
    connect(item, SIGNAL(positionChanged(ImageItem*,double,double)),
            this, SLOT(updateImagePosition(ImageItem*,double,double)));
    connect(item, SIGNAL(resized(ImageItem*,double)),
            this, SLOT(resizeImageItem(ImageItem*,double)));
    connect(item, SIGNAL(deleted(ImageItem*)),
            this, SLOT(deleteImage(ImageItem*)));

    connect(item, &ImageItem::animationApplied,
            this, &Timeline::animationApplied);
    connect(item, &ImageItem::imageSelected,
            this, &Timeline::imageSelected);
    connect(item, &ImageItem::blurTypeApplied,
            this, &Timeline::blurTypeApplied);

    auto temp = new SizeGripItem(new ImageItemResizer, item);
    temp->setMaxWidth(std::numeric_limits<double>::infinity());
    item->createSizeGripItem(temp);

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
    if (item->start.key() == start && item->end.key() == end)
        return;
    // delete old duration
    deleteImage(item);

    // add new duration
    item->start = imageMap.insert(start, item);
    item->end = imageMap.insert(end, nullptr);
    emit imageAdded(item->image, start, end-start, item->animation);
}