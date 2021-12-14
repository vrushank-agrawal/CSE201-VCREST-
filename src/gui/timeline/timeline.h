//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#ifndef VIDEO_EDITOR_BX23_TIMELINE_H
#define VIDEO_EDITOR_BX23_TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QResizeEvent>
#include <QListWidgetItem>
#include <imageitem.h>
#include "indicator.h"
#include "image.h"

using namespace img;

class Timeline: public QGraphicsView {
Q_OBJECT
public:
    explicit Timeline(QWidget *parent = 0);
    ~Timeline();
    static double default_image_length;
    void updateVideoLength(int length);
    void addImage(Image *image, double start, double end); // add an Image at the specified location
    void appendImage(Image *image, double length=default_image_length); // append an Image to the end of the timeline
    void addImageAtIndicator(Image *image, double max_length = default_image_length); // call appendImage if an image already exists
    Image* getImage(qreal time);
    Image* getImageAtIndicator();

signals:
    void videoLengthChanged(int length);
    void timeIndicatorChanged(qreal time);


private:
    int sceneWidth = 120, sceneHeight = 120;
    qreal sceneShowingWidth = 3000;
    qreal currentXPosition = 0;
    int timeHeight = 20;
    int xTimeOffset = 100, yTime = 0;
    int lengthInSecond = 10 * 60;
    QGraphicsScene *scene = nullptr;
    Indicator *indicator = nullptr;
    QMultiMap<double, ImageItem*> map;

    enum TimelineMoveOption{
        KeepCurrentPosition,
        CenterIndicator,
    };

    void moveTimeline(TimelineMoveOption option);
    void setItemPosition(ImageItem *item, double startTime);
    ImageItem* getImageItem(double time);

private slots:
    void moveImageItem(ImageItem *item, double startPos, double endPos);
    void updateIndicatorPosition(double);
    void updateTime(qreal xPosition);
    void updateImagePosition(ImageItem* item, double start, double end);
    void resizeImageItem(ImageItem *item, double newLength);
    void deleteImage(ImageItem*);

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
};

#endif //VIDEO_EDITOR_BX23_TIMELINE_H
