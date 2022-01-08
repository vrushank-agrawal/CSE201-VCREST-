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
    void updateVideoLength(double duration);

signals:
    void playStateChanged(bool isPlaying);
    void timeUpdated(double currentTime);
    void seekAudioRequested(double currentTime);

public slots:
    void updateCurrentTime(double time);
    void updateFrame(cv::Mat frame);
    void sliderPressed();
    void sliderReleased();
    void forward();
    void backward();
    void play();

private slots:
    void updateTime();

private:
    void updatePlayButton();

    bool isPlaying = false;
    bool isMoving = false;
    int fps = 30;
    double currentTime = 0, videoLength = 0;
    QToolButton *playButton = nullptr;
    QTimer *timer = nullptr;
    VideoWindow *label = nullptr;
};

#endif //VIDEO_EDITOR_BX23_VIDEOPLAYER_H
