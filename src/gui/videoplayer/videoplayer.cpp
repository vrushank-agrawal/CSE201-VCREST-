//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#include <QStyle>
#include <iostream>
#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent) :
        QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VideoPlayer::updateTime);
    timer->start(1000 / fps);
    timer->stop();
}

VideoPlayer::~VideoPlayer()
{
    delete timer;
}

void VideoPlayer::updateFrame(cv::Mat frame){
    QImage qimg(frame.data,
                frame.cols,
                frame.rows,
                frame.step,
                QImage::Format_RGB888);
    label->setOriginalPixmap(QPixmap::fromImage(qimg.rgbSwapped()));
    label->updatePixmap();
}

void VideoPlayer::updateTime(){
    currentTime += 1.0 / fps;
    cv::Mat frame;

    emit timeUpdated(currentTime);
}

void VideoPlayer::updateCurrentTime(double time) {
    if (currentTime == time) return;
    currentTime = time;

    emit timeUpdated(currentTime);
}

void VideoPlayer::setChild(VideoWindow *label,
                           QToolButton *playButton)
{
    this->label = label;

    this->playButton = playButton;
    this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    this->playButton->setToolTip(tr("Play"));
}

void VideoPlayer::play(){
    isPlaying = !isPlaying;
    updatePlayButton();
    emit playStateChanged(isPlaying);
}

void VideoPlayer::sliderPressed(){
    isMoving = true;
    updatePlayButton();
}

void VideoPlayer::sliderReleased() {
    isMoving = false;
    updatePlayButton();
}

void VideoPlayer::forward(){
    currentTime = std::max(currentTime + 5, 0.0);
    emit timeUpdated(currentTime);
}

void VideoPlayer::backward(){
    currentTime = std::min(currentTime - 5, videoLength);
    emit timeUpdated(currentTime);
}

void VideoPlayer::updatePlayButton(){
    if (!isPlaying || isMoving) {
        this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        this->playButton->setToolTip(tr("Play"));

        timer->stop();
    }
    else {
        this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        this->playButton->setToolTip(tr("Pause"));

        timer->start();
    }
}