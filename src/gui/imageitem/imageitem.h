//
// Created by nhatv on 4 Dec 2021.
//

#ifndef VIDEO_EDITOR_BX23_IMAGEITEM_H
#define VIDEO_EDITOR_BX23_IMAGEITEM_H


#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "image.h"
#include "sizegripitem.h"
#include "imageitemmenu.h"

class ImageItem: public QObject, public QGraphicsItem
{
Q_OBJECT
Q_INTERFACES(QGraphicsItem)

public:
    explicit ImageItem(img::Image *image,
                       QPoint position
                       );
    ~ImageItem();
    static ImageItem* getSelectedImageItem() {return selectedImageItem;}

    static double yOffset, xTimeOffset, yHeight;
    constexpr static const double border = 3;
    int blurLevel = 1;
    QMultiMap<double, ImageItem*>::iterator start, end;
    img::Image *image;
    void setSize(QSizeF size);
    void calculateSize();
    void updateDuration(double newLength);
    void createSizeGripItem(SizeGripItem *sizeGripItem);
    void resetImage();
    static QTransform parentTransform;
    vid::Animation animation = vid::Normal;

private:
    SizeGripItem *sizeGripItem = nullptr;
    static QBrush brush, selectedBrush;
    static QPen pen, selectedPen;
    static ImageItem *selectedImageItem;
    QSizeF size;
    bool pressed=false;
    QPointF oldPos,oldMousePos;
    ImageItemMenu *menu;

signals:
    void itemMoved(ImageItem *item, double start, double end);
    void positionChanged(ImageItem* item, double start, double end);
    void resized(ImageItem* item, double newLength);
    void deleted(ImageItem*);
    void animationApplied(img::Image* image, vid::Animation animation);
    void imageSelected();

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual double getTimeOfFrame();

public slots:
    void applyAnimation(vid::Animation);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif //VIDEO_EDITOR_BX23_IMAGEITEM_H
