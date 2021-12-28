//
// Created by nhatv on 28 Dec 2021.
//

#ifndef VIDEO_EDITOR_BX23_AUDIOITEM_H
#define VIDEO_EDITOR_BX23_AUDIOITEM_H


#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "sizegripitem.h"

class AudioItem : public QObject, public QGraphicsItem {
Q_OBJECT
Q_INTERFACES(QGraphicsItem)

public:
    explicit AudioItem(QString audioSource,
                       QPoint position);
    ~AudioItem();

    static double yOffset, xTimeOffset, yHeight;
    constexpr static const double border = 3;

    QString audioSource;
    QMultiMap<double, AudioItem*>::iterator start, end;

    void calculateSize();
    void createSizeGripItem(SizeGripItem *sizeGripItem);
    void updateDuration(double newLength);
    void setSize(QSizeF size);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    static QBrush brush;
    static QPen pen;

    QPointF oldPos,oldMousePos;
    bool pressed=false;
    SizeGripItem *sizeGripItem = nullptr;
    QSizeF size;


signals:
    void deleted(AudioItem*);
    void itemMoved(AudioItem *item, double start, double end);
    void positionChanged(AudioItem* item, double start, double end);
    void resized(AudioItem* item, double newLength);


protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif //VIDEO_EDITOR_BX23_AUDIOITEM_H
