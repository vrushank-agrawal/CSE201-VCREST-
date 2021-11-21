//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#ifndef VIDEO_EDITOR_BX23_VIDEOPLAYER_H
#define VIDEO_EDITOR_BX23_VIDEOPLAYER_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include "videowindow.h"

#include "opencv2/opencv.hpp"

class VideoPlayer : public QWidget
{
Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();
    void setQLabel(VideoWindow *label);

private slots:
    void updatePicture();

private:
    QTimer *timer;
    VideoWindow *label;
    cv::VideoCapture video;
};

#endif //VIDEO_EDITOR_BX23_VIDEOPLAYER_H
