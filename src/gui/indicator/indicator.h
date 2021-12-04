//
// Created by Minh Tung Nguyen on 04/12/2021.
//

#ifndef VIDEO_EDITOR_BX23_INDICATOR_H
#define VIDEO_EDITOR_BX23_INDICATOR_H


#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QLine>
#include <QPolygonF>
#include <QVector>
#include <QPointF>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Indicator:public QGraphicsItem
{
public:
    Indicator(qreal height);

    QSizeF calculateSize() const;
    void setHeight(qreal height){line.setP2(QPoint(0,height));}

    QVector<QPointF> points; // polygons for the head
    QBrush brush;
    QPen pen;
    QLine line;
    bool pressed=false;
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};

#endif //VIDEO_EDITOR_BX23_INDICATOR_H