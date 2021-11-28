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
    using namespace cv;

    Mat frame;
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


void VideoPlayer::setChild(VideoWindow *label, QToolButton *playButton){
    this->label = label;
    this->playButton = playButton;

    this->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    this->playButton->setToolTip(tr("Play"));
    connect(this->playButton, SIGNAL(clicked()), this, SLOT(play()));
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

void VideoPlayer::updateVideo(cv::VideoCapture video) {
    this->video = video;
    if (timer != nullptr) delete timer;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
    double fps = video.get(cv::CAP_PROP_FPS);
    std::cout << fps << std::endl;
    timer->start(int(1000 / fps));
}