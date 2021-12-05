//
// Created by nhatv on 4 Dec 2021.
//

#include "imageitem.h"

double ImageItem::yHeight = 40;
double ImageItem::yOffset = 20;
double ImageItem::xTimeOffset = 100;
QBrush ImageItem::brush = QBrush(Qt::RoundCap);
QPen ImageItem::pen = QPen(Qt::black, border);


ImageItem::ImageItem(Image *image,
                     QPointF duration,
                     QPoint position
                     ): image(image), duration(duration) {
    Mat mat = image->getModifiedImg();
    QImage qImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    thumbnail = QPixmap::fromImage(qImage.rgbSwapped());
    setPos(QPoint(position.x(), position.y() + yOffset));
    calculateSize();
}

ImageItem::~ImageItem() {
}

QRectF ImageItem::boundingRect() const {
    return QRectF(0, 0, size.width() + border * 2, size.height() + border * 2);
}

void ImageItem::calculateSize() {
    double width = (duration.y() - duration.x()) * xTimeOffset;
    size = QSizeF(width, yHeight);
}

void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(pen);
    painter->drawRoundedRect(boundingRect(), border, border);
    double wScale = size.width() / thumbnail.width();
    QRectF thumbnailRect(0,0, thumbnail.width(), thumbnail.height());
    painter->drawPixmap(
            QRectF(
                    border / 2,
                    border / 2,
                    (thumbnail.width() * wScale > size.width()) ? size.width() : thumbnail.width() * wScale + border,
                    size.height() + border
                    ),
            thumbnail,
            thumbnailRect
            );
}

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    pressed = true;
    oldMousePos = event->scenePos();
    oldPos = scenePos();
}

void ImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (pressed){
        QPointF newPos = event->scenePos();
        int dx = (newPos - oldMousePos).x();
        setX(oldPos.x()+dx);
    }
}

void ImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    pressed = false;
    oldMousePos = event->scenePos();
    oldPos = scenePos();
    QPointF newDuration(oldPos.x() / xTimeOffset, oldPos.x() / xTimeOffset + duration.y() - duration.x());
    emit positionChanged(duration, newDuration);
    duration = newDuration;
}

QVariant ImageItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}
