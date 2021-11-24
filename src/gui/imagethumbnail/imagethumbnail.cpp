//
// Created by nhatv on 24 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ImageThumbnail.h" resolved

#include <QVBoxLayout>
#include <QLabel>
#include "imagethumbnail.h"


ImageThumbnail::ImageThumbnail(const QPixmap& image, const QString& name, QWidget *parent= nullptr) : QWidget(parent) {
    this->setFixedSize(60, 80);
    this->setStyleSheet("background: white; border: 1px solid black");
    this->image = new QLabel();
    this->name = new QLabel();

    QSizePolicy imageSize(QSizePolicy::Preferred, QSizePolicy::Preferred);
    imageSize.setHorizontalStretch(0);
    imageSize.setVerticalStretch(5);
    imageSize.setHeightForWidth(this->image->sizePolicy().hasHeightForWidth());
    this->image->setSizePolicy(imageSize);

    QSizePolicy nameSize(QSizePolicy::Preferred, QSizePolicy::Preferred);
    nameSize.setHorizontalStretch(0);
    nameSize.setVerticalStretch(1);
    nameSize.setHeightForWidth(this->name->sizePolicy().hasHeightForWidth());
    this->name->setSizePolicy(nameSize);

    this->image->setPixmap(image);
    this->name->setText(name);


    container = new QVBoxLayout(this);
    container->addWidget(this->image, 5, Qt::AlignHCenter);
    container->addWidget(this->name, 1, Qt::AlignHCenter);

    container->setAlignment(Qt::AlignHCenter);
}

ImageThumbnail::~ImageThumbnail() {
    delete image;
    delete name;
    delete container;
}

