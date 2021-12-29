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
    void applyNormalAnimation() { emit animationChoosed(vid::Normal); };
    void applyRotationAnimation() { emit animationChoosed(vid::Rotation); };
    void applyZoomingAnimation() { emit animationChoosed(vid::Zooming); };
    void applyCroppingAnimation() { emit animationChoosed(vid::Cropping); };

private:
    QMenu *animationMenu = nullptr;
    QAction *normalAnimationAction = nullptr;
    QAction *rotationAnimationAction = nullptr;
    QAction *zoomingAnimationAction = nullptr;
    QAction *croppingAnimationAction = nullptr;
};

#endif //VIDEO_EDITOR_BX23_IMAGEITEMMENU_H
