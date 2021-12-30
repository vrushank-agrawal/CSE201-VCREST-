//
// Created by Minh Tung Nguyen on 21/11/2021.
//

#include "videowindow.h"

VideoWindow::VideoWindow(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    blackScene = scene->addRect(0, 0, width, height, QPen(Qt::black), Qt::black);
    scene->setSceneRect(0, 0, width, height);
    fitInView(blackScene, Qt::KeepAspectRatio);
    centerOn(blackScene);
}

VideoWindow::~VideoWindow() {
    delete graphicsPixmap;
    delete scene;
}

void VideoWindow::setOriginalPixmap(QPixmap pixmap) {
    original_pixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio);
}

void VideoWindow::updatePixmap() {
    if (!original_pixmap.isNull()){
        delete graphicsPixmap;
        graphicsPixmap = new QGraphicsPixmapItem(original_pixmap);
        scene->addItem(graphicsPixmap);
        graphicsPixmap->setOffset((width - original_pixmap.width()) / 2, (height - original_pixmap.height()) / 2);
    }
    fitInView(blackScene, Qt::KeepAspectRatio);
    centerOn(blackScene);
}

void VideoWindow::resizeEvent(QResizeEvent *event) {
    updatePixmap();
    QWidget::resizeEvent(event);
}