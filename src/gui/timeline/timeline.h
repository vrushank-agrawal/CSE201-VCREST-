//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#ifndef VIDEO_EDITOR_BX23_TIMELINE_H
#define VIDEO_EDITOR_BX23_TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QResizeEvent>
#include "indicator.h"
#include "image.h"

using namespace img;

class Timeline: public QGraphicsView {
Q_OBJECT
public:
    explicit Timeline(QWidget *parent = 0);
    ~Timeline();
    void updateVideoLength(int length);
    void addImage(Image *image, QPointF duration);
    Image* getImage(qreal time);

signals:
    void videoLengthChanged(int length);
    void timeIndicatorChanged(qreal time);

private:
    int sceneWidth = 120, sceneHeight = 120;
    qreal sceneShowingWidth = 3000;
    int timeHeight = 20;
    int xTimeOffset = 100, yTime = 0;
    int lengthInSecond = 10 * 60;
    QGraphicsScene *scene = nullptr;
    Indicator *indicator = nullptr;
    QMap<double, Image*> map;

    void moveTimeline();

private slots:
    void updateIndicatorPosition(double);
    void updateTime(qreal xPosition);
    void updateImagePosition(QPointF prevDuration, QPointF newDuration);

protected:
    virtual void resizeEvent(QResizeEvent *event);
};

#endif //VIDEO_EDITOR_BX23_TIMELINE_H
