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
    void animationChosen(vid::Animation);
    void blurChosen(img::BlurType);

public slots:
    void applyNormalAnimation() ;
    void applyRotationAnimation();
    void applyZoomingAnimation();
    void applyCroppingAnimation();
    void applyNormalBlur();
    void applyGaussianBlur();
    void applyMedianBlur();

private:
    QMenu *animationMenu = nullptr;
    QMenu *blurMenu = nullptr;
    QAction *normalAnimationAction = nullptr;
    QAction *rotationAnimationAction = nullptr;
    QAction *zoomingAnimationAction = nullptr;
    QAction *croppingAnimationAction = nullptr;
    QAction *normalBlurAction = nullptr;
    QAction *gaussianBlurAction = nullptr;
    QAction *medianBlurAction = nullptr;
};

#endif //VIDEO_EDITOR_BX23_IMAGEITEMMENU_H
