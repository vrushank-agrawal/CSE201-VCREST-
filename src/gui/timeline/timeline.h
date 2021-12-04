//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#ifndef VIDEO_EDITOR_BX23_TIMELINE_H
#define VIDEO_EDITOR_BX23_TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QResizeEvent>

class Timeline: public QGraphicsView {
Q_OBJECT
public:
    explicit Timeline(QWidget *parent = 0);
    ~Timeline();

private:
    int xTimeOffset = 100, yTime = 0;
    int lengthInSecond = 10 * 60;
    QGraphicsScene *scene;
};

#endif //VIDEO_EDITOR_BX23_TIMELINE_H