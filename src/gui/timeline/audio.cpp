//
// Created by nhatv on 2 Jan 2022.
//

#include "audioresizer.h"
#include "timeline.h"

double Timeline::default_audio_length = 5;

void Timeline::addAudio(audio::Audio* audio, QString displayName, double sourceLength, double start, double end) {
    auto *item = new AudioItem(audio, displayName, sourceLength, QPoint(start * xTimeOffset, AudioItem::border));
    end = (item->getMaxLength() < 500) ? start + item->getMaxLength()*0.01 : end;
    item->start = audioMap.insert(start, item);
    item->end = audioMap.insert(end, nullptr);
    item->calculateSize();
    scene->addItem(item);

    connect(item, SIGNAL(itemMoved(AudioItem*,double,double)),
            this, SLOT(moveAudioItem(AudioItem*,double,double)));
    connect(item, SIGNAL(positionChanged(AudioItem*,double,double)),
            this, SLOT(updateAudioPosition(AudioItem*,double,double)));
    connect(item, SIGNAL(resized(AudioItem*,double)),
            this, SLOT(resizeAudioItem(AudioItem*,double)));
    connect(item, SIGNAL(deleted(AudioItem*)),
            this, SLOT(deleteAudio(AudioItem*)));

    SizeGripItem *sizeGripItem = new SizeGripItem(new AudioItemResizer, item);
    sizeGripItem->setMaxWidth(item->getMaxLength());

    item->createSizeGripItem(sizeGripItem);
}

void Timeline::appendAudio(audio::Audio* audio, QString displayName, double sourceLength, double length) {
    double start = audioMap.isEmpty() ? 0 : audioMap.lastKey();
    addAudio(audio, displayName, sourceLength, start, start + length);
}

void Timeline::addAudioAtIndicator(audio::Audio* audio, QString displayName, double sourceLength, double max_length) {
    double time = indicator->x() / xTimeOffset;

    // audio already exists
    if (getAudioItem(time) != nullptr) {
        appendAudio(audio, displayName, sourceLength, max_length);
        return;
    }

    QMultiMap<double, AudioItem*>::iterator end = audioMap.upperBound(time);
    double duration;
    if (end == audioMap.end()) // trying to append image at the end of timeline
        duration = max_length;
    else
        duration = (end.key() - time > max_length) ? max_length : end.key() - time;
    addAudio(audio, displayName, sourceLength, time, time + duration);
}

void Timeline::deleteAudio(AudioItem *item) {
    audioMap.erase(item->start);
    audioMap.erase(item->end);
    emit audioDeleted(item->audio);
}

audio::Audio* Timeline::getAudio(qreal time) {
    AudioItem *item = getAudioItem(time);
    if (item != nullptr) return item->audio;
    return nullptr;
}

AudioItem* Timeline::getAudioItem(double time) {
    QMultiMap<double, AudioItem*>::iterator iterator = getAudioIterator(time);
    return (iterator == audioMap.end()) ? nullptr : iterator.value();
}

QMultiMap<double, AudioItem *>::iterator Timeline::getAudioIterator(double time) {
    QMultiMap<double, AudioItem*>::iterator iterator = audioMap.upperBound(time);

    // find the greatest key smaller than this key
    if (iterator == audioMap.begin()) return audioMap.end();
    iterator--;
    iterator = audioMap.find(iterator.key());

    // ignore nullptr
    while (iterator != audioMap.end() && iterator.key() <= time) {
        if (iterator.value() != nullptr)
            return iterator;
        iterator++;
    }
    return audioMap.end();
}

double Timeline::getAudioStartTime(double time) {
    QMultiMap<double, AudioItem *>::iterator iterator = getAudioIterator(time);
    return (iterator == audioMap.end()) ? -1 : iterator.key();
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
    newLength = std::min(newLength, item->getMaxLength());
    double startTime = item->x() / xTimeOffset;
    double endTime = (item->x() + newLength) / xTimeOffset;

    // detect collision with other audios
    QMultiMap<double, AudioItem*>::iterator iterator = audioMap.lowerBound(startTime);
    while (iterator != audioMap.end() && iterator.key() < endTime) {
        if (iterator.value() != nullptr && iterator.value() != item) {
            item->updateDuration((iterator.key() - startTime) * xTimeOffset);
            emit seekAudioRequested(indicator->x() / xTimeOffset);
            return;
        }
        iterator++;
    }
    item->updateDuration(newLength);
    emit seekAudioRequested(indicator->x() / xTimeOffset);
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

    if (end > lengthInSecond) {
        int newEnd = ceil(end / 5) * 5;
        updateVideoLength(newEnd + 30);
    }

    emit audioAdded(item->audio, start, end-start);
    emit seekAudioRequested(indicator->x() / xTimeOffset);
}