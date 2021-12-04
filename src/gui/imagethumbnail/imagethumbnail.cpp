//
// Created by nhatv on 24 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ImageThumbnail.h" resolved

#include "imagethumbnail.h"

ThumbnailManager::ThumbnailManager(QListWidget *qListWidget) : listWidget(qListWidget) {
    qListWidget->setDragEnabled(true);
    qListWidget->setViewMode(QListView::IconMode);
    qListWidget->setIconSize(QSize(50, 50));
    qListWidget->setGridSize(QSize(80, 90));
    qListWidget->setSpacing(20);
    qListWidget->setContentsMargins(20, 20, 20, 20);
    qListWidget->setMovement(QListView::Snap);
    qListWidget->setAcceptDrops(true);
    qListWidget->setDropIndicatorShown(true);
    qListWidget->setWordWrap(true);
    qListWidget->setUniformItemSizes(true);
    qListWidget->setAutoScrollMargin(100);

    brush = QBrush(Qt::white);
}

void ThumbnailManager::addImage(Image image, const QString& name) {
    images.append(image);
    Mat mat = image.getModifiedImg();
    QImage qImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    addImage(
            QPixmap::fromImage(qImage.rgbSwapped()),
            name
            );
}

void ThumbnailManager::addImage(const QPixmap& image, const QString& name) {
    QString displayName;
    if (name.lastIndexOf("/") >= 0) {
        displayName = name.right(name.length() - name.lastIndexOf("/") - 1);
    }
    else {
        displayName = name;
    }

    auto *item = new QListWidgetItem(QIcon(image),displayName);
    item->setBackground(brush);
    item->setSizeHint(QSize(60, 70));
    listWidget->addItem(item);
}

ThumbnailManager::~ThumbnailManager() {
    delete listWidget;
}

int ThumbnailManager::getImagesCount() {
    return images.length();
}

Image* ThumbnailManager::getImage(int index) {
    if (index >= getImagesCount()) {
        return nullptr;
    }
    return &images[index];
}

void ThumbnailManager::removeImage(int index) {
    if (index >= getImagesCount()) {
        return;
    }
    images.remove(index);
}

//void ThumbnailManager::

