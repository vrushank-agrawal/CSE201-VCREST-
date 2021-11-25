//
// Created by nhatv on 24 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ImageThumbnail.h" resolved

#include <QVBoxLayout>
#include <QLabel>
#include "imagethumbnail.h"

ImageThumbnail::ImageThumbnail(const QPixmap& image, const QString& name, QWidget *parent= nullptr) : QWidget(parent) {
    container = new QWidget(this);
    this->setFixedSize(120, 160);
    this->setStyleSheet("background: white; border: 1px solid black");
    this->image = new QLabel();
    this->name = new QLabel();

    this->image->setPixmap(image.scaled(40, 40, Qt::KeepAspectRatio));
    this->name->setText(name);

    qvBoxLayout = new QVBoxLayout(container);
    qvBoxLayout->addWidget(this->image, 5, Qt::AlignHCenter);
    qvBoxLayout->addWidget(this->name, 1, Qt::AlignHCenter);

    qvBoxLayout->setAlignment(Qt::AlignHCenter);
}

ImageThumbnail::~ImageThumbnail() {
    delete container;
    delete image;
    delete name;
    delete qvBoxLayout;
}

