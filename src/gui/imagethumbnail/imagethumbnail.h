//
// Created by nhatv on 24 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H
#define VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "opencv2/opencv.hpp"
#include "image.h"

using namespace cv;
using namespace img;

class ThumbnailManager {

public:
    explicit ThumbnailManager(QListWidget *qListWidget);
    ~ThumbnailManager();
    void addImage(Image image, const QString& name);

    // will be made private
    void addImage(const QPixmap& image, const QString& name);
    int getImagesCount();
    Image* getImage(int index);
    void removeImage(int index);
    void removeAllImages(int index);

private:
    QListWidget *listWidget;
    QBrush brush;
    QVector<Image> images;
};


#endif //VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H
