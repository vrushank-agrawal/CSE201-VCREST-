//
// Created by Minh Tung Nguyen on 26/12/2021.
//

#ifndef VIDEO_EDITOR_BX23_IMAGEITEMMENU_H
#define VIDEO_EDITOR_BX23_IMAGEITEMMENU_H

#include <QMenu>
#include "video.h"

class ImageItemMenu: public QMenu {
Q_OBJECT

public:
    explicit ImageItemMenu(QWidget *parent = nullptr);
    ~ImageItemMenu() override;

signals:
    void animationChoosed(vid::Animation);

public slots:
    void applyNormalAnimation() {
        normalAnimationAction->setText(QString::fromUtf8("Normal ✓"));
        rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
        zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));
        croppingAnimationAction->setText(QString::fromUtf8("Cropping"));
        emit animationChoosed(vid::Normal);
    };
    void applyRotationAnimation() {
        normalAnimationAction->setText(QString::fromUtf8("Normal"));
        rotationAnimationAction->setText(QString::fromUtf8("Rotation ✓"));
        zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));
        croppingAnimationAction->setText(QString::fromUtf8("Cropping"));
        emit animationChoosed(vid::Rotation);
    };
    void applyZoomingAnimation() {
        normalAnimationAction->setText(QString::fromUtf8("Normal"));
        rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
        zoomingAnimationAction->setText(QString::fromUtf8("Zooming ✓"));
        croppingAnimationAction->setText(QString::fromUtf8("Cropping"));
        emit animationChoosed(vid::Zooming);
    };
    void applyCroppingAnimation() {
        normalAnimationAction->setText(QString::fromUtf8("Normal"));
        rotationAnimationAction->setText(QString::fromUtf8("Rotation"));
        zoomingAnimationAction->setText(QString::fromUtf8("Zooming"));
        croppingAnimationAction->setText(QString::fromUtf8("Cropping ✓"));
        emit animationChoosed(vid::Cropping);
    };

private:
    QMenu *animationMenu = nullptr;
    QAction *normalAnimationAction = nullptr;
    QAction *rotationAnimationAction = nullptr;
    QAction *zoomingAnimationAction = nullptr;
    QAction *croppingAnimationAction = nullptr;
};

#endif //VIDEO_EDITOR_BX23_IMAGEITEMMENU_H
