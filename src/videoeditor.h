//
// Created by nhatv on 11 Nov 2021.
//

#ifndef VIDEO_EDITOR_BX23_VIDEOEDITOR_H
#define VIDEO_EDITOR_BX23_VIDEOEDITOR_H

#include <QMainWindow>
#include <QListView>
#include <audiomanager.h>
#include <imagethumbnail.h>
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui { class VideoEditor; }
QT_END_NAMESPACE

class VideoEditor : public QMainWindow {
Q_OBJECT

public:
    explicit VideoEditor(QWidget *parent = nullptr);
    ~VideoEditor() override;

signals:
    void imageChanged();
    void positionChanged(int position);
    void currentTimeChanged(double timeInSec);

public slots:
    void importMedia();
    void importImages();
    void importAudios();
    void blurImage();
    void updatePosition(int position);
    void updateCurrentTime(double time);
    void appendImageToThumbnail(QListWidgetItem*);
    void writeVideo();

private:
    cv::VideoCapture video;
    QSet<QString> imageFileTypes;
    QSet<QString> audioFileTypes;
    QString imageFileTypesFilter;
    QString audioFileTypesFilter;
    int position = 0, fps = 30;
    double timeInSec;
    Ui::VideoEditor *ui;
    std::vector<QPixmap> images;
    int imageIndex = -1; // index of image need to displayed in images
    void updateVideo(const cv::VideoCapture &video);
    void setupVideoPlayer();
    void setupMenus();
    void setupWidgets();
    QStringList importFiles(const QString& caption, const QString& startingDirectory, const QString& filter);
    void importImage(const QString& dir);
    void importAudio(const QString& dir);
    ThumbnailManager *thumbnailManager;
    AudioManager *audioManager;

    int fourcc;

//    std::string outputPath = "D:/Downloads/2.mp4";
};


#endif //VIDEO_EDITOR_BX23_VIDEOEDITOR_H
