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

class ThumbnailManager {

public:
    explicit ThumbnailManager(QListWidget *qListWidget);
    ~ThumbnailManager();
    void addImage(const cv::Mat& image, const QString& name);
    void addImage(const QPixmap& image, const QString& name);

private:
    QListWidget *listWidget;
    QList<QListWidgetItem> *listItems;
    QBrush *brush;
};


#endif //VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H
