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
    delete label;
    delete timer;
}

void VideoPlayer::updatePicture(){
    if (!isPlaying) return;

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
        }
    }
}

void VideoPlayer::setChild(VideoWindow *label,
                           QToolButton *playButton,
                           QToolButton *skipForward,
                           QToolButton *skipBackward,
                           QSlider *slider)
{
    this->label = label;

    this->playButton = playButton;
    this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    this->playButton->setToolTip(tr("Play"));
    connect(this->playButton, SIGNAL(clicked()), this, SLOT(play()));

    this->skipForward = skipForward;
    this->skipForward->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    this->skipBackward = skipBackward;
    this->skipBackward->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    this->slider = slider;
    this->slider->setRange(0, 0);
    this->slider->setTracking(true);
    connect(this->slider, SIGNAL(sliderPressed()),
            this, SLOT(sliderPressed()));
    connect(this->slider, SIGNAL(sliderMoved(int)),
            this, SLOT(sliderMoved(int)));
}

void VideoPlayer::play(){
    if (isPlaying) {
        this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        this->playButton->setToolTip(tr("Play"));
    }
    else {
        this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        this->playButton->setToolTip(tr("Play"));
    }
    isPlaying = !isPlaying;
}

void VideoPlayer::sliderMoved(int position){
    video.set(cv::CAP_PROP_POS_FRAMES, slider->value());
}

void VideoPlayer::sliderPressed(){
    video.set(cv::CAP_PROP_POS_FRAMES, slider->value());
}

void VideoPlayer::positionChanged() {
    slider->setValue(video.get(cv::CAP_PROP_POS_FRAMES));
}

void VideoPlayer::updateVideo(cv::VideoCapture video) {
    this->video = video;

    this->slider->setRange(0, video.get(cv::CAP_PROP_FRAME_COUNT));
    if (timer != nullptr) delete timer;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
    connect(timer, SIGNAL(timeout()), this, SLOT(positionChanged()));
    double fps = video.get(cv::CAP_PROP_FPS);
    timer->start(int(1000 / fps));
}