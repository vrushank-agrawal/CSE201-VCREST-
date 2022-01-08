//
// Created by Minh Tung Nguyen on 26/12/2021.
//

#include "imageitemmenu.h"

ImageItemMenu::ImageItemMenu(QWidget *parent): QMenu(parent) {
    // create animation menu
    animationMenu = new QMenu(this);
    animationMenu->setTitle("Animation");
    blurMenu = new QMenu(this);
    blurMenu->setTitle("Blur");

    normalAnimationAction = new QAction(animationMenu);
    normalAnimationAction->setObjectName(QString::fromUtf8("normalAnimationAction"));
    normalAnimationAction->setText(QString::fromUtf8("Normal ✓"));

    rotationAnimationAction = new QAction(animationMenu);
    rotationAnimationAction->setObjectName(QString::fromUtf8("rotationAnimationAction"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));

    zoomInAnimationAction = new QAction(animationMenu);
    zoomInAnimationAction->setObjectName(QString::fromUtf8("Zoom InAnimationAction"));
    zoomInAnimationAction->setText(QString::fromUtf8("Zoom In"));

    zoomOutAnimationAction = new QAction(animationMenu);
    zoomOutAnimationAction->setObjectName(QString::fromUtf8("zoomOutAnimationAction"));
    zoomOutAnimationAction->setText(QString::fromUtf8("Zoom Out"));

    fadeInAnimationAction = new QAction(animationMenu);
    fadeInAnimationAction->setObjectName(QString::fromUtf8("fadeInAnimationAction"));
    fadeInAnimationAction->setText(QString::fromUtf8("Fade In"));

    fadeOutAnimationAction = new QAction(animationMenu);
    fadeOutAnimationAction->setObjectName(QString::fromUtf8("fadeOutAnimationAction"));
    fadeOutAnimationAction->setText(QString::fromUtf8("Fade Out"));

    normalBlurAction = new QAction(blurMenu);
    normalBlurAction->setObjectName(QString::fromUtf8("normalBlurAction"));
    normalBlurAction->setText(QString::fromUtf8("Normal ✓"));

    gaussianBlurAction = new QAction(blurMenu);
    gaussianBlurAction->setObjectName(QString::fromUtf8("gaussianBlurAction"));
    gaussianBlurAction->setText(QString::fromUtf8("Gaussian"));

    medianBlurAction = new QAction(blurMenu);
    medianBlurAction->setObjectName(QString::fromUtf8("medianBlurAction"));
    medianBlurAction->setText(QString::fromUtf8("Median"));

    animationMenu->addAction(normalAnimationAction);
    animationMenu->addAction(rotationAnimationAction);
    animationMenu->addAction(zoomInAnimationAction);
    animationMenu->addAction(zoomOutAnimationAction);
    animationMenu->addAction(fadeInAnimationAction);
    animationMenu->addAction(fadeOutAnimationAction);

    blurMenu->addAction(normalBlurAction);
    blurMenu->addAction(gaussianBlurAction);
    blurMenu->addAction(medianBlurAction);


    connect(normalAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyNormalAnimation);
    connect(rotationAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyRotationAnimation);
    connect(zoomInAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyZoomInAnimation);
    connect(zoomOutAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyZoomOutAnimation);
    connect(fadeInAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyFadeInAnimation);
    connect(fadeOutAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyFadeOutAnimation);

    connect(normalBlurAction, &QAction::triggered,
            this, &ImageItemMenu::applyNormalBlur);
    connect(gaussianBlurAction, &QAction::triggered,
            this, &ImageItemMenu::applyGaussianBlur);
    connect(medianBlurAction, &QAction::triggered,
            this, &ImageItemMenu::applyMedianBlur);

    addMenu(animationMenu);
    addMenu(blurMenu);
}

ImageItemMenu::~ImageItemMenu() {
    delete animationMenu;
}

void ImageItemMenu::applyNormalAnimation()  {
    normalAnimationAction->setText(QString::fromUtf8("Normal ✓"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
    zoomInAnimationAction->setText(QString::fromUtf8("Zoom In"));
    zoomOutAnimationAction->setText(QString::fromUtf8("Zoom Out"));
    fadeInAnimationAction->setText(QString::fromUtf8("Fade In"));
    fadeOutAnimationAction->setText(QString::fromUtf8("Fade Out"));
    emit animationChosen(vid::Normal);
}

void ImageItemMenu::applyRotationAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation ✓"));
    zoomInAnimationAction->setText(QString::fromUtf8("Zoom In"));
    zoomOutAnimationAction->setText(QString::fromUtf8("Zoom Out"));
    fadeInAnimationAction->setText(QString::fromUtf8("Fade In"));
    fadeOutAnimationAction->setText(QString::fromUtf8("Fade Out"));
    emit animationChosen(vid::Rotation);
}

void ImageItemMenu::applyZoomInAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
    zoomInAnimationAction->setText(QString::fromUtf8("Zoom In ✓"));
    zoomOutAnimationAction->setText(QString::fromUtf8("Zoom Out"));
    fadeInAnimationAction->setText(QString::fromUtf8("Fade In"));
    fadeOutAnimationAction->setText(QString::fromUtf8("Fade Out"));
    emit animationChosen(vid::ZoomIn);
}

void ImageItemMenu::applyZoomOutAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
    zoomInAnimationAction->setText(QString::fromUtf8("Zoom In"));
    zoomOutAnimationAction->setText(QString::fromUtf8("Zoom Out ✓"));
    fadeInAnimationAction->setText(QString::fromUtf8("Fade In"));
    fadeOutAnimationAction->setText(QString::fromUtf8("Fade Out"));
    emit animationChosen(vid::ZoomOut);
}

void ImageItemMenu::applyFadeInAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
    zoomInAnimationAction->setText(QString::fromUtf8("Zoom In"));
    zoomOutAnimationAction->setText(QString::fromUtf8("Zoom Out"));
    fadeInAnimationAction->setText(QString::fromUtf8("Fade In ✓"));
    fadeOutAnimationAction->setText(QString::fromUtf8("Fade Out"));
    emit animationChosen(vid::FadeIn);
}

void ImageItemMenu::applyFadeOutAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
    zoomInAnimationAction->setText(QString::fromUtf8("Zoom In"));
    zoomOutAnimationAction->setText(QString::fromUtf8("Zoom Out"));
    fadeInAnimationAction->setText(QString::fromUtf8("Fade In"));
    fadeOutAnimationAction->setText(QString::fromUtf8("Fade Out ✓"));
    emit animationChosen(vid::FadeOut);
}

void ImageItemMenu::applyNormalBlur() {
    normalBlurAction->setText(QString::fromUtf8("Normal ✓"));
    gaussianBlurAction->setText(QString::fromUtf8("Gaussian"));
    medianBlurAction->setText(QString::fromUtf8("Median"));
    emit blurChosen(img::BlurType::Normal);
}

void ImageItemMenu::applyGaussianBlur() {
    normalBlurAction->setText(QString::fromUtf8("Normal"));
    gaussianBlurAction->setText(QString::fromUtf8("Gaussian ✓"));
    medianBlurAction->setText(QString::fromUtf8("Median"));
    emit blurChosen(img::BlurType::Gaussian);
}

void ImageItemMenu::applyMedianBlur() {
    normalBlurAction->setText(QString::fromUtf8("Normal"));
    gaussianBlurAction->setText(QString::fromUtf8("Gaussian"));
    medianBlurAction->setText(QString::fromUtf8("Median ✓"));
    emit blurChosen(img::BlurType::Median);
}
