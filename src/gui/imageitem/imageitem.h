//
// Created by nhatv on 4 Dec 2021.
//

#ifndef VIDEO_EDITOR_BX23_IMAGEITEM_H
#define VIDEO_EDITOR_BX23_IMAGEITEM_H


#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include "image.h"

using namespace img;

class ImageItem: public QObject, public QGraphicsItem
{
Q_OBJECT
public:
    explicit ImageItem(Image *image, QSizeF size, QPoint position);
    ~ImageItem();


private:
    Image *image;
    static QBrush brush;
    static QPen pen;
    static qreal yOffset, border;
    QSizeF size;
    QPointF position;
    QPixmap thumbnail;

signals:
    void positionChanged(qreal time);

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


#endif //VIDEO_EDITOR_BX23_IMAGEITEM_H
