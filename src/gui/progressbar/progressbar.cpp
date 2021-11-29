//
// Created by Minh Tung Nguyen on 29/11/2021.
//

#include "progressbar.h"
#include <iostream>

ProgressBar::ProgressBar(QWidget *parent) :
        QSlider(Qt::Horizontal, parent)
{

}

ProgressBar::~ProgressBar() {

}

void ProgressBar::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        int position = minimum() + ((maximum()-minimum()) * event->x()) / width();
        setValue(position) ;
        event->accept();
        emit frameUpdate(position);
    }
    emit QSlider::mouseReleaseEvent(event);
}

void ProgressBar::mouseMoveEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        int position = minimum() + ((maximum()-minimum()) * event->x()) / width();
        setValue(position) ;
        event->accept();
        emit frameUpdate(position);
    }
    emit QSlider::mouseMoveEvent(event);
}

void ProgressBar::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        int position = minimum() + ((maximum()-minimum()) * event->x()) / width();
        setValue(position) ;
        event->accept();
        emit frameUpdate(position);
    }
    emit QSlider::mousePressEvent(event);
}