//
// Created by nhatv on 4 Dec 2021.
//

#include "imageitem.h"

ImageItem::ImageItem(Image *image, qreal width, qreal height): image(image), width(width), height(height) {
    brush = QBrush(Qt::RoundCap);
    pen = QPen(Qt::black, 20);
    Mat mat = image->getModifiedImg();
    QImage qImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    thumbnail = QPixmap::fromImage(qImage);
}

ImageItem::~ImageItem() {
}

QRectF ImageItem::boundingRect() const {
    return QRectF(0, 0, width+20, height+20);
}

void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(pen);
//    painter->drawRect(boundingRect());
    QRect thumbnailSize(0,0, thumbnail.width(), thumbnail.height());
    painter->drawPixmap(boundingRect(), thumbnail, thumbnailSize);
}

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mousePressEvent(event);
}

void ImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
}

void ImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant ImageItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}
