//
// Created by nhatv on 24 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_IMAGEMANAGER_H
#define VIDEO_EDITOR_BX23_IMAGEMANAGER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "opencv2/opencv.hpp"
#include "image.h"

class ImageManager {

public:
    explicit ImageManager(QListWidget *qListWidget);
    ~ImageManager();
    void addImage(img::Image image, const QString& name);

    // will be made private
    void addImage(const QPixmap& image, const QString& name, img::Image *img=nullptr);
    int getImagesCount();
    img::Image* getImage(QListWidgetItem *item);
    img::Image* getImage(int row);

private:
    QListWidget *listWidget = nullptr;
    QBrush brush;
    QMap<QListWidgetItem*, img::Image> map;
};


#endif //VIDEO_EDITOR_BX23_IMAGEMANAGER_H
