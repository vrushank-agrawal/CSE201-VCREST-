//
// Created by nhatv on 7 Dec 2021.
//

#include <QGraphicsItem>
#include "audioresizer.h"


void AudioItemResizer::operator()(QGraphicsItem *item, const QRectF &rect) {
    AudioItem *audioItem = dynamic_cast<AudioItem*>(item);
    if (audioItem) {
        emit audioItem->resized(audioItem, rect.width());
    }
}