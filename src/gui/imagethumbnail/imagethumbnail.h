//
// Created by nhatv on 24 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H
#define VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class ImageThumbnail : public QWidget {
Q_OBJECT

public:
    explicit ImageThumbnail(const QPixmap& image, const QString& name, QWidget* parent);
    ~ImageThumbnail() override;

private:
    QVBoxLayout *container;
    QLabel *image;
    QLabel *name;
};


#endif //VIDEO_EDITOR_BX23_IMAGETHUMBNAIL_H
