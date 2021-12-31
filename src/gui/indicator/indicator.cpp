//
// Created by Minh Tung Nguyen on 04/12/2021.
//

#include "indicator.h"
#include "time.h"
#include <thread>

Indicator::Indicator(qreal height): QGraphicsItem ()
{
    pen = QPen(Qt::black,2);
    brush = QBrush(Qt::RoundCap);
    brush.setColor(QColor("#F2F200"));
    points<<QPointF(0,10)
          <<QPointF(-10,0)
          <<QPointF(10,0);
    setHeight(height * 2);
    setAcceptHoverEvents(true);
    this->setAcceptDrops(true);

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

Indicator::~Indicator() {

}

QSizeF Indicator::calculateSize()const
{
    qreal minX = points[0].x();
    qreal minY = points[0].y();
    qreal maxX = points[0].x();
    qreal maxY = points[0].y();
    for(QPointF point : points){
        if (point.x() < minX){
            minX = point.x();
        }
        if (point.y() < minY){
            minY = point.y();
        }
        if (point.x() > maxX){
            maxX = point.x();
        }
        if (point.y() > maxY){
            maxY = point.y();
        }
    }
    return QSizeF(maxX-minX,line.p2().y());
}

QRectF Indicator::boundingRect() const
{
    QSizeF size = this->calculateSize();
    return QRectF(-10,-10,size.width(),size.height());
}

void Indicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->drawLine(line);
    painter->setBrush(brush);
    painter->drawPolygon(&points[0], points.size());
}

void Indicator::updateWhenPressed() {
    while (pressed) {
        if (difftime(time(0), lastUpdateTime) > 0.045) {
            emit positionChanged(this->x());
            lastUpdateTime = time(0);
        }
    }
}

void Indicator::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    emit playStateChanged(false);
    lastUpdateTime = std::time(0);
    std::thread updateThread(&Indicator::updateWhenPressed, this);
    updateThread.detach();
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Indicator::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    if(pressed && pos.x() >= 0){
        this->setPos(pos.x(),y());
    }
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void Indicator::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    emit playStateChanged(true);
    if (event->scenePos().x() >= 0) {
        emit positionChanged(event->scenePos().x());
    }
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

QVariant Indicator::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        newPos.setY(y());
        if(newPos.x() < 0){
            newPos.setX(0);
        }
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}
