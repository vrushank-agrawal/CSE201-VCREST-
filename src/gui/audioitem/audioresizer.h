//
// Created by nhatv on 7 Dec 2021.
//

#ifndef VIDEO_EDITOR_BX23_IMAGERESIZER_H
#define VIDEO_EDITOR_BX23_RESIZER_H

#include "sizegripitem.h"
#include "audioitem.h"

class AudioItemResizer : public SizeGripItem::Resizer {
public:
    virtual void operator()(QGraphicsItem* item, const QRectF& rect);
};


#endif //VIDEO_EDITOR_BX23_IMAGERESIZER_H
