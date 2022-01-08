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

    connect(item, &AudioItem::itemMoved,
            this, &Timeline::moveAudioItem);
    connect(item, &AudioItem::positionChanged,
            this, &Timeline::updateAudioPosition);
    connect(item, &AudioItem::resized,
            this, &Timeline::resizeAudioItem);
    connect(item, &AudioItem::deleted,
            this, &Timeline::deleteAudio);

    auto *sizeGripItem = new SizeGripItem(new AudioItemResizer, item);
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

std::string Timeline::createAudio() {
    double currentTime = 0;
    audio::Audio currentAudio = audio::createSilence(0);
    for (auto iterator = audioMap.begin(); iterator != audioMap.end(); iterator++) {
        if (iterator.value() == nullptr) continue;
        double start = iterator.key(), end = iterator.value()->end.key();
        audio::Audio *curAudio = iterator.value()->audio;
        if (abs(currentTime - start) >= 1e3) {
            std::string newName = audio::createSilence(int((start - currentTime) * 1000));
            audio::Audio silentAudio = audio::Audio(newName);
            currentAudio = audio::merge(currentAudio, silentAudio);
        }
        std::string audioName = audio::trim(*curAudio, int((end - start) * 1000), true);
        audio::Audio newAudio = audio::Audio(audioName);
        currentAudio = audio::merge(currentAudio, audioName);
    }

    return currentAudio.getURI();
}

void Timeline::deleteAudio(AudioItem *item) {
    audioMap.erase(item->start);
    audioMap.erase(item->end);
    emit audioDeleted(item->audio);
}

AudioItem* Timeline::getAudioItem(double time) {
    QMultiMap<double, AudioItem*>::iterator iterator = getAudioIterator(time);
    return (iterator == audioMap.end()) ? nullptr : iterator.value();
}

QMultiMap<double, AudioItem *>::iterator Timeline::getAudioIterator(double time) {
    for (auto iterator = audioMap.begin(); iterator != audioMap.end(); iterator++) {
        if (iterator.value() == nullptr) continue;
        double startTime = iterator.value()->start.key(), endTime = iterator.value()->end.key();

        if (startTime <= time + eps && time - eps <= endTime) return iterator;
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