//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#include <QCoreApplication>
#include "videoplayer.h"
#include <iostream>

VideoPlayer::VideoPlayer(QWidget *parent) :
        QWidget(parent)
{
    video.open("/Users/minhtung0404/Downloads/1.mp4");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
    timer->start(20);
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