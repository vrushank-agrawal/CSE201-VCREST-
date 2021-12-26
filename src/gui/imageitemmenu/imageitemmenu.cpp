//
// Created by Minh Tung Nguyen on 26/12/2021.
//

#include "imageitemmenu.h"

ImageItemMenu::ImageItemMenu(QWidget *parent): QMenu(parent) {
    // create animation menu
    animationMenu = new QMenu(this);
    animationMenu->setTitle("Animation");

    normalAnimationAction = new QAction(animationMenu);
    normalAnimationAction->setObjectName(QString::fromUtf8("normalAnimationAction"));
    normalAnimationAction->setText(QString::fromUtf8("Normal"));

    rotationAnimationAction = new QAction(animationMenu);
    rotationAnimationAction->setObjectName(QString::fromUtf8("rotationAnimationAction"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));

    zoomingAnimationAction = new QAction(animationMenu);
    zoomingAnimationAction->setObjectName(QString::fromUtf8("zoomingAnimationAction"));
    zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));

    croppingAnimationAction = new QAction(animationMenu);
    croppingAnimationAction->setObjectName(QString::fromUtf8("croppingAnimationAction"));
    croppingAnimationAction->setText(QString::fromUtf8("Cropping"));

    animationMenu->addAction(normalAnimationAction);
    animationMenu->addAction(rotationAnimationAction);
    animationMenu->addAction(zoomingAnimationAction);
    animationMenu->addAction(croppingAnimationAction);

    connect(normalAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyNormalAnimation);
    connect(rotationAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyRotationAnimation);
    connect(zoomingAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyZoomingAnimation);
    connect(croppingAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyCroppingAnimation);

    addMenu(animationMenu);
}

ImageItemMenu::~ImageItemMenu() {
    delete animationMenu;
}
