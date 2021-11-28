//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#ifndef VIDEO_EDITOR_BX23_VIDEOPLAYER_H
#define VIDEO_EDITOR_BX23_VIDEOPLAYER_H

#include <QMainWindow>
#include <QDebug>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QToolButton>
#include <QSlider>
#include "videowindow.h"

#include "opencv2/opencv.hpp"

class VideoPlayer : public QWidget
{
Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();
    void setChild(VideoWindow *label,
                  QToolButton *playButton);
    void updateVideo(const cv::VideoCapture &video);

signals:
    void updateSlider(int position);

private slots:
    void updatePicture();
    void play();
    void sliderPressed();
    void sliderMoved(int position);
    void sliderReleased();
    void forward();
    void backward();

private:
    bool isPlaying = false;
    bool isMoving = false;
    QToolButton *playButton;
    QTimer *timer = nullptr;
    VideoWindow *label;
    cv::VideoCapture video;
};

#endif //VIDEO_EDITOR_BX23_VIDEOPLAYER_H
