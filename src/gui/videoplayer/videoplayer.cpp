//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#include <QCoreApplication>
#include "videoplayer.h"
#include <iostream>

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


void VideoPlayer::setQLabel(VideoWindow *label){
    this->label = label;
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