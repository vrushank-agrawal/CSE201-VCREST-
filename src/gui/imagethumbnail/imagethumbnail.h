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

using namespace cv;

class ThumbnailManager {

public:
    explicit ThumbnailManager(QListWidget *qListWidget);
    ~ThumbnailManager();
    void addImage(cv::Mat image, const QString& name);
    void addImage(const QPixmap& image, const QString& name);
    int getImagesCount();
    Mat* getImage(int index);
    void removeImage(int index);
    void removeAllImages(int index);

private:
    QListWidget *listWidget;
    QBrush brush;
    QVector<Mat> images;
};


#endif //VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H
