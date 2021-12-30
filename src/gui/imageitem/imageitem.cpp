//
// Created by nhatv on 4 Dec 2021.
//

#include "imageitem.h"

double ImageItem::yHeight = 40;
double ImageItem::yOffset = 20;
double ImageItem::xTimeOffset = 100;
ImageItem* ImageItem::selectedImageItem = nullptr;
QBrush ImageItem::brush = QBrush(Qt::black);
QPen ImageItem::pen = QPen(Qt::black, border);
QBrush ImageItem::selectedBrush = QBrush(Qt::gray);
QPen ImageItem::selectedPen = QPen(Qt::blue, border);
QTransform ImageItem::parentTransform = QTransform();

ImageItem::ImageItem(img::Image *image,
                     QPoint position
                     ): image(image) {
    setPos(QPoint(position.x(), position.y() + yOffset));
    size = QSizeF();
    menu = new ImageItemMenu();
    connect(menu, &ImageItemMenu::animationChoosed, this, &ImageItem::applyAnimation);
}


ImageItem::~ImageItem() {
    selectedImageItem = nullptr;
    delete image;
    delete sizeGripItem;
    delete menu;
}

QRectF ImageItem::boundingRect() const {
    return QRectF(0, 0, size.width() + border * 2, size.height() + border * 2);
}

void ImageItem::setSize(QSizeF size) {
    prepareGeometryChange();
    this->size = size;
}

void ImageItem::calculateSize() {
    prepareGeometryChange();
    double width = (end.key() - start.key()) * xTimeOffset;
    size = QSizeF(width, yHeight);
}

void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(selectedImageItem == this ? selectedPen : pen);
    painter->setBrush(selectedImageItem == this? selectedBrush : brush);
    painter->drawRoundedRect(boundingRect(), border, border);

    cv::Mat mat = image->getModifiedImg();
    QImage qImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    QPixmap thumbnail = QPixmap::fromImage(qImage.rgbSwapped());

    double wScale = size.width() / thumbnail.width();
    QRectF thumbnailRect(0,0, thumbnail.width(), thumbnail.height());

    qreal height = size.height() + border;
    qreal width = (size.height() + border) * parentTransform.m22() / thumbnail.height() * thumbnail.width() / parentTransform.m11();
    width = std::min(width, size.width());

    painter->drawPixmap(
            QRectF(
                    border / 2,
                    border / 2,
                    width,
                    height
                    ),
            thumbnail,
            thumbnailRect
            );
}

void ImageItem::applyAnimation(vid::Animation animation) {
    this->animation = animation;
    emit animationApplied(image, animation);
}

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (selectedImageItem != this) {
            auto oldSelected = selectedImageItem;
            selectedImageItem = this;
            this->update();
            if (oldSelected != nullptr) oldSelected->update();
        }
        else {
            selectedImageItem = nullptr;
            this->update();
        }
        pressed = true;
        oldMousePos = event->scenePos();
        oldPos = scenePos();
        emit imageSelected();
    }
    else if (event->button() == Qt::RightButton) {
        menu->exec(event->screenPos());
    }
}

void ImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (pressed){
        QPointF newPos = event->scenePos();
        double dx = (newPos - oldMousePos).x();
        double start = oldPos.x() + dx;
        double end = start + size.width();
        emit itemMoved(this, start, end);
    }
}

void ImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    pressed = false;
    oldMousePos = event->scenePos();
    oldPos = scenePos();
    double s = oldPos.x() / xTimeOffset;
    double e = oldPos.x() / xTimeOffset + end.key() - start.key();
    emit positionChanged(this, s, e);
}

void ImageItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    emit deleted(this);
    delete this;
}

void ImageItem::updateDuration(double newLength) {
    prepareGeometryChange();
    size = QSizeF(newLength, size.height());
    sizeGripItem->resize(boundingRect());
    emit positionChanged(this, this->start.key(), this->start.key() + newLength / xTimeOffset);
}

void ImageItem::createSizeGripItem(SizeGripItem *sizeGripItem) {
    this->sizeGripItem = sizeGripItem;
}

double ImageItem::getTimeOfFrame() {
    return ((this->pos().x() + this->size.width()/2.0)/100.0);
}

void ImageItem::resetImage() {
    image->setModifiedImg(image->getMat().clone());
    image->setCurrentUnblurImg(image->getMat().clone());
}

void ImageItem::unblurImage() {
    image->setModifiedImg(image->getCurrentUnblurImg().clone());
}


