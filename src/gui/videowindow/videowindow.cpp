//
// Created by Minh Tung Nguyen on 21/11/2021.
//

#include "videowindow.h"

VideoWindow::VideoWindow(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
}

VideoWindow::~VideoWindow() {
    delete graphicsPixmap;
}

void VideoWindow::setOriginalPixmap(QPixmap pixmap) {
    original_pixmap = pixmap;
}

void VideoWindow::updatePixmap() {
    if (!original_pixmap.isNull()){
        delete graphicsPixmap;
        graphicsPixmap = new QGraphicsPixmapItem(original_pixmap);
        scene->addItem(graphicsPixmap);
        fitInView(graphicsPixmap, Qt::KeepAspectRatio);
    }
}

void VideoWindow::resizeEvent(QResizeEvent *event) {
    updatePixmap();
    QWidget::resizeEvent(event);
}