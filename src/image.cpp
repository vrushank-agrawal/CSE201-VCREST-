//
// Created by nhatv on 2 Jan 2022.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"

void VideoEditor::addImageToResultVideo(img::Image *image, double startTime, double duration, vid::Animation animation) {
    resultVideo->addImage(image, startTime, duration);
    resultVideo->applyAnimation(image, animation);
    updateFrame();
}

void VideoEditor::appendImageToThumbnail(QListWidgetItem* item) {
    auto *image = new img::Image(imageManager->getImage(item)->getMat());
    ui->timeline->addImageAtIndicator(image);
}

void VideoEditor::applyAnimation(img::Image *image, vid::Animation animation) {
    resultVideo->applyAnimation(image, animation);
}

void VideoEditor::applyBlur(ImageItem *imageItem) {
    imageItem->blur();
    imageItem->update();
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::blurImage() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (blurSlider->isVisible()) {
        blurSlider->setVisible(false);
        return;
    }
    QPoint pos = ui->blurButton->mapToGlobal(QPoint(0, 0));
    blurSlider->move(pos.x()-blurSlider->width(), pos.y());
    blurSlider->setVisible(true);
    if (imageItem == nullptr) return;
    imageItem->blur();
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::deleteImageFromResultVideo(img::Image *image) {
    resultVideo->deleteImage(image);
    updateFrame();
}

void VideoEditor::imageSelected() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) {
        updateFrame();
    }
    else {
        blurSlider->setValue(imageItem->blurLevel);
        cv::Mat frame = imageItem->image->getModifiedImg();
        emit changeFrame(frame);
    }
}

void VideoEditor::resetImage() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    imageItem->resetImage();
    imageItem->update();
    imageItem->blurLevel = 0;
    blurSlider->setValue(0);
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::rotateImageRight() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    imageItem->image->rotateImgFit(-90.0);
    imageItem->update();
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::updateBlurLevel() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    imageItem->blurLevel = blurSlider->value();
    imageItem->blur();
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::updateFrame() {
    cv::Mat frame = resultVideo->getMatByTime(timeInSec);
    emit changeFrame(frame);
}