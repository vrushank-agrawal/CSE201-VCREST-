//
// Created by Minh Tung Nguyen on 21/11/2021.
//

#ifndef VIDEO_EDITOR_BX23_VIDEOWINDOW_H
#define VIDEO_EDITOR_BX23_VIDEOWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QResizeEvent>

class VideoWindow: public QLabel
{
Q_OBJECT
public:
    explicit VideoWindow(QWidget *parent = 0);
    ~VideoWindow();

    void setOriginalPixmap(QPixmap);
    void updatePixmap();

private:
    QPixmap original_pixmap;
protected:
    virtual void resizeEvent(QResizeEvent *event);
};

#endif //VIDEO_EDITOR_BX23_VIDEOWINDOW_H
