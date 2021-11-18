//
// Created by Minh Tung Nguyen on 18/11/2021.
//

#include "videoplayer.h"
#include <iostream>

VideoPlayer::VideoPlayer(QWidget *parent) :
        QWidget(parent)
{
    video.open("/Users/minhtung0404/Downloads/1.mp4");
}

VideoPlayer::~VideoPlayer()
{
    delete graphicsView;
}

void VideoPlayer::play(){
    using namespace cv;

    Mat frame;
    int cnt = 100;
    while(video.isOpened())
    {
        video >> frame;
        std::cerr << "new frame " << frame.empty() << std::endl;
        if(!frame.empty())
        {
            copyMakeBorder(frame,
                           frame,
                           frame.rows,
                           frame.rows,
                           frame.cols,
                           frame.cols,
                           BORDER_CONSTANT);

            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
//            graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        }
        cnt--;
        if (!cnt) break;
    }
}


void VideoPlayer::setGraphicsView(QGraphicsView *graphicsView){
    this->graphicsView = graphicsView;
    this->graphicsView->setScene(new QGraphicsScene(this));
    this->graphicsView->scene()->addItem(&pixmap);
//    this->graphicsView->setFixedSize(500, 250);
}