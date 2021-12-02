//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#include <QStyle>
#include <iostream>
#include "videoplayer.h"

VideoPlayer::VideoPlayer(QWidget *parent) :
        QWidget(parent)
{
}

VideoPlayer::~VideoPlayer()
{
    delete timer;
}

void VideoPlayer::updatePicture(){
    cv::Mat frame;
    if (video.isOpened())
    {
        video >> frame;
        if(!frame.empty())
        {
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            label->setOriginalPixmap(QPixmap::fromImage(qimg.rgbSwapped()));
            label->updatePixmap();
            label->update();
            emit frameUpdated(video.get(cv::CAP_PROP_POS_FRAMES));
        }
    }
}

void VideoPlayer::setChild(VideoWindow *label,
                           QToolButton *playButton)
{
    this->label = label;

    this->playButton = playButton;
    this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    this->playButton->setToolTip(tr("Play"));
}

void VideoPlayer::updateVideo(const cv::VideoCapture &video) {
    this->video = video;

    if (timer != nullptr) delete timer;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
    double fps = this->video.get(cv::CAP_PROP_FPS);
    timer->start(int(1000 / fps));
    timer->stop();
}

void VideoPlayer::play(){
    isPlaying = !isPlaying;
    updatePlayButton();
}

void VideoPlayer::sliderPressed(){
    isMoving = true;
    updatePlayButton();
}

void VideoPlayer::updateFrame(int position){
    if (position != video.get(cv::CAP_PROP_POS_FRAMES)) {
        video.set(cv::CAP_PROP_POS_FRAMES, position-1);
        updatePicture();
    }
}

void VideoPlayer::sliderReleased() {
    isMoving = false;
    updatePlayButton();
}

void VideoPlayer::forward(){
    int currentFrame = video.get(cv::CAP_PROP_POS_FRAMES);
    int fps = video.get(cv::CAP_PROP_FPS);
    int newFrame = std::min(int(video.get(cv::CAP_PROP_FRAME_COUNT)), currentFrame + fps * 5);
    video.set(cv::CAP_PROP_POS_FRAMES, newFrame);
    emit frameUpdated(newFrame);
}

void VideoPlayer::backward(){
    int currentFrame = video.get(cv::CAP_PROP_POS_FRAMES);
    int fps = video.get(cv::CAP_PROP_FPS);
    int newFrame = std::max(0, currentFrame - fps * 5);
    video.set(cv::CAP_PROP_POS_FRAMES, newFrame);
    emit frameUpdated(newFrame);
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