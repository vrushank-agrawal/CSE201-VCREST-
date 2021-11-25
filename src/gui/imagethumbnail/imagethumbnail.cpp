//
// Created by nhatv on 24 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ImageThumbnail.h" resolved

#include "imagethumbnail.h"

ThumbnailManager::ThumbnailManager(QListWidget *qListWidget) : listWidget(qListWidget) {
    qListWidget->setDragEnabled(true);
    qListWidget->setViewMode(QListView::IconMode);
    qListWidget->setIconSize(QSize(50, 50));
    qListWidget->setGridSize(QSize(70, 80));
    qListWidget->setSpacing(10);
    qListWidget->setContentsMargins(10, 10, 10, 10);
    qListWidget->setMovement(QListView::Snap);
    qListWidget->setAcceptDrops(true);
    qListWidget->setDropIndicatorShown(true);
    qListWidget->setWordWrap(true);

    brush = new QBrush(Qt::white);
}

void ThumbnailManager::addImage(const cv::Mat& image, const QString& name) {
    QImage qImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    addImage(
            QPixmap::fromImage(qImage),
            name
            );
}

void ThumbnailManager::addImage(const QPixmap& image, const QString& name) {
    auto *item = new QListWidgetItem(QIcon(image),name);
    item->setBackground(*brush);
    listWidget->addItem(item);
}

ThumbnailManager::~ThumbnailManager() {
    delete listWidget;
}

