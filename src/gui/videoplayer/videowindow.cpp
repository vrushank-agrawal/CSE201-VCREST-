//
// Created by Minh Tung Nguyen on 21/11/2021.
//

#include "videowindow.h"
#include <QWidget>

VideoWindow::VideoWindow(QWidget *parent): QLabel(parent) {
}

VideoWindow::~VideoWindow() {
};

void VideoWindow::setOriginalPixmap(QPixmap pixmap) {
    original_pixmap = pixmap;
}

void VideoWindow::updatePixmap() {
    setPixmap(original_pixmap.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void VideoWindow::resizeEvent(QResizeEvent *event) {
    resize(event->size());
    updatePixmap();
    QWidget::resizeEvent(event);
}