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
    constexpr static const double border = 3;
    static double yOffset, xTimeOffset, yHeight;
    static QTransform parentTransform;

    img::BlurType blurType = img::BlurType::Normal;
    vid::Animation animation = vid::Animation::Normal;
    int blurLevel = 0;
    img::Image *image = nullptr;
    QMultiMap<double, ImageItem*>::iterator start, end;

    void calculateSize();
    void createSizeGripItem(SizeGripItem *sizeGripItem);
    double getTimeOfFrame();
    void resetImage();
    void unblurImage();
    void setSize(QSizeF size);
    void updateDuration(double newLength);
    int getMedianBlueLevel();
    void blur();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    static QBrush brush, selectedBrush;
    static QPen pen, selectedPen;
    static ImageItem *selectedImageItem;

    ImageItemMenu *menu = nullptr;
    QPointF oldPos,oldMousePos;
    bool pressed=false;
    QSizeF size;
    SizeGripItem *sizeGripItem = nullptr;


signals:
    void animationApplied(img::Image* image, vid::Animation animation);
    void blurTypeApplied(ImageItem* imageItem);
    void deleted(ImageItem*);
    void imageSelected();
    void itemMoved(ImageItem *item, double start, double end);
    void positionChanged(ImageItem* item, double start, double end);
    void resized(ImageItem* item, double newLength);


public slots:
    void applyAnimation(vid::Animation);
    void applyBlur(img::BlurType);


protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif //VIDEO_EDITOR_BX23_IMAGEITEM_H
