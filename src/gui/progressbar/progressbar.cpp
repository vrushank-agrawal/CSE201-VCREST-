//
// Created by Minh Tung Nguyen on 29/11/2021.
//

#include "progressbar.h"
#include <iostream>
#include <thread>
#include "time.h"

ProgressBar::ProgressBar(QWidget *parent) :
        QSlider(Qt::Horizontal, parent)
{

}

ProgressBar::~ProgressBar() {
}

void ProgressBar::updateWhenPress() {
    while (pressed) {
        if (difftime(time(0), lastUpdateTime) > 0.045) {
            emit frameChanged(value());
            lastUpdateTime = time(0);
        }
    }
}

void ProgressBar::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        pressed = false;
        int position = minimum() + ((maximum()-minimum()) * event->pos().x()) / width();
        position = std::max(position, minimum());
        position = std::min(position, maximum());
        setValue(position) ;
        event->accept();
        emit frameChanged(position);
    }
    emit QSlider::mouseReleaseEvent(event);
}

void ProgressBar::mouseMoveEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        int position = minimum() + ((maximum()-minimum()) * event->pos().x()) / width();
        setValue(position) ;
        event->accept();
//        emit frameUpdate(position);
    }
    emit QSlider::mouseMoveEvent(event);
}

void ProgressBar::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        pressed = true;
        lastUpdateTime = time(0);
        std::thread updateThread(&ProgressBar::updateWhenPress, this);
        updateThread.detach();
        int position = minimum() + ((maximum()-minimum()) * event->pos().x()) / width();
        setValue(position);
        event->accept();
        emit frameChanged(position);
    }
    emit QSlider::mousePressEvent(event);
}