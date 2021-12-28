//
// Created by nhatv on 28 Dec 2021.
//

#include "audioitem.h"


double AudioItem::yHeight = 40;
double AudioItem::yOffset = 60;
double AudioItem::xTimeOffset = 100;
QBrush AudioItem::brush = QBrush(Qt::black);
QPen AudioItem::pen = QPen(Qt::black, border);


AudioItem::AudioItem(QString audioSource, QPoint position) : audioSource(audioSource) {
    setPos(QPoint(position.x(), position.y() + yOffset));
    size = QSizeF();
}

AudioItem::~AudioItem() {

}

void AudioItem::setSize(QSizeF size) {
    prepareGeometryChange();
    this->size = size;
}

void AudioItem::calculateSize() {
    prepareGeometryChange();
    double width = (end.key() - start.key()) * xTimeOffset;
    size = QSizeF(width, yHeight);
}

void AudioItem::updateDuration(double newLength) {
    prepareGeometryChange();
    size = QSizeF(newLength, size.height());
    sizeGripItem->resize(boundingRect());
    emit positionChanged(this, this->start.key(), this->start.key() + newLength / xTimeOffset);
}

void AudioItem::createSizeGripItem(SizeGripItem *sizeGripItem) {
    this->sizeGripItem = sizeGripItem;
}

QRectF AudioItem::boundingRect() const {
    return QRectF(0, 0, size.width() + border * 2, size.height() + border * 2);
}

void AudioItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawRoundedRect(boundingRect(), border, border);
}

void AudioItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    pressed = true;
    oldMousePos = event->scenePos();
    oldPos = scenePos();
}

void AudioItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (pressed){
        QPointF newPos = event->scenePos();
        double dx = (newPos - oldMousePos).x();
        double start = oldPos.x() + dx;
        double end = start + size.width();
        emit itemMoved(this, start, end);
    }
}

void AudioItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    pressed = false;
    oldMousePos = event->scenePos();
    oldPos = scenePos();
    double s = oldPos.x() / xTimeOffset;
    double e = oldPos.x() / xTimeOffset + end.key() - start.key();
    emit positionChanged(this, s, e);
}

void AudioItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    emit deleted(this);
    delete this;
}
