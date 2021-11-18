//
// Created by nhatv on 11 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_VIDEOEDITOR_H
#define VIDEO_EDITOR_BX23_VIDEOEDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class VideoEditor; }
QT_END_NAMESPACE

class VideoEditor : public QMainWindow {
Q_OBJECT

public:
    explicit VideoEditor(QWidget *parent = nullptr);

    ~VideoEditor() override;

public slots:
    void ImportImage();
    void SetAudioTimeSpan();

private:
    Ui::VideoEditor *ui;
    double audioLength = 0.0; // Audio Length in minutes
    double audioTimeSpan;

    double Round2Decimal(double d) {
        double value = (int)(d * 100 + .5);
        return (double)value / 100.0;
    }
};


#endif //VIDEO_EDITOR_BX23_VIDEOEDITOR_H
