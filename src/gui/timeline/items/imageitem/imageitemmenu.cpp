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

    zoomingAnimationAction = new QAction(animationMenu);
    zoomingAnimationAction->setObjectName(QString::fromUtf8("zoomingAnimationAction"));
    zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));

    croppingAnimationAction = new QAction(animationMenu);
    croppingAnimationAction->setObjectName(QString::fromUtf8("croppingAnimationAction"));
    croppingAnimationAction->setText(QString::fromUtf8("Cropping"));

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
//    animationMenu->addAction(zoomingAnimationAction);
//    animationMenu->addAction(croppingAnimationAction);

    blurMenu->addAction(normalBlurAction);
    blurMenu->addAction(gaussianBlurAction);
    blurMenu->addAction(medianBlurAction);


    connect(normalAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyNormalAnimation);
    connect(rotationAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyRotationAnimation);
    connect(zoomingAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyZoomingAnimation);
    connect(croppingAnimationAction, &QAction::triggered,
            this, &ImageItemMenu::applyCroppingAnimation);

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
    zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));
    croppingAnimationAction->setText(QString::fromUtf8("Cropping"));
    emit animationChosen(vid::Normal);
}

void ImageItemMenu::applyRotationAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation ✓"));
    zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));
    croppingAnimationAction->setText(QString::fromUtf8("Cropping"));
    emit animationChosen(vid::Rotation);
}

void ImageItemMenu::applyZoomingAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
    zoomingAnimationAction->setText(QString::fromUtf8("Zooming ✓"));
    croppingAnimationAction->setText(QString::fromUtf8("Cropping"));
    emit animationChosen(vid::ZoomIn);
}

void ImageItemMenu::applyCroppingAnimation() {
    normalAnimationAction->setText(QString::fromUtf8("Normal"));
    rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
    zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));
    croppingAnimationAction->setText(QString::fromUtf8("Cropping ✓"));
//    emit animationChosen(vid::Cropping);
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
