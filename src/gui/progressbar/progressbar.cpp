//
// Created by Minh Tung Nguyen on 29/11/2021.
//

#include "progressbar.h"

ProgressBar::ProgressBar(QWidget *parent) :
        QSlider(Qt::Horizontal, parent)
{

}

ProgressBar::~ProgressBar() {

}

void ProgressBar::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ) ;
        else
            setValue(minimum() + ((maximum()-minimum()) * event->x()) / width() ) ;

        event->accept();
    }
    emit QSlider::mouseReleaseEvent(event);
}

void ProgressBar::mouseMoveEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ) ;
        else
            setValue(minimum() + ((maximum()-minimum()) * event->x()) / width() ) ;

        event->accept();
    }
    emit QSlider::mouseMoveEvent(event);
}

void ProgressBar::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum()-minimum()) * (height()-event->y())) / height() ) ;
        else
            setValue(minimum() + ((maximum()-minimum()) * event->x()) / width() ) ;

        event->accept();
    }
    emit QSlider::mousePressEvent(event);
}