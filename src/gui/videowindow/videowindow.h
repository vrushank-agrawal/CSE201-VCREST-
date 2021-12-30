//
// Created by Minh Tung Nguyen on 21/11/2021.
//

#ifndef VIDEO_EDITOR_BX23_VIDEOWINDOW_H
#define VIDEO_EDITOR_BX23_VIDEOWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QResizeEvent>

class VideoWindow: public QGraphicsView
{
Q_OBJECT
public:
    explicit VideoWindow(QWidget *parent = nullptr);
    ~VideoWindow();
    void setOriginalPixmap(QPixmap);
    void updatePixmap();
    void setSize(int width, int height) {this->width = width; this->height = height;};

private:
    QPixmap original_pixmap;
    QGraphicsPixmapItem *graphicsPixmap = nullptr;
    QGraphicsItem *blackScene = nullptr;
    QGraphicsScene *scene = nullptr;
    int width = 1280, height = 720;
protected:
    virtual void resizeEvent(QResizeEvent *event);
};

#endif //VIDEO_EDITOR_BX23_VIDEOWINDOW_H
