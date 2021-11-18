//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#ifndef VIDEO_EDITOR_BX23_VIDEOPLAYER_H
#define VIDEO_EDITOR_BX23_VIDEOPLAYER_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>

#include "opencv2/opencv.hpp"

class VideoPlayer : public QWidget
{
Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();
    void play();
    void setGraphicsView(QGraphicsView *graphicsView);

private:
    QGraphicsView *graphicsView;
    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;
};

#endif //VIDEO_EDITOR_BX23_VIDEOPLAYER_H
