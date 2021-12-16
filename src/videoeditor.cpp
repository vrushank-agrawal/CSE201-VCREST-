//
// Created by nhatv on 11 Nov 2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_VideoEditor.h" resolved

#include "videoeditor.h"
#include "ui_VideoEditor.h"
#include <QFileDialog>
#include "image.h"


VideoEditor::VideoEditor(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::VideoEditor) {
    ui->setupUi(this);
    setupVideoPlayer();
    setupMenus();
    setupWidgets();

    // add video to preview
    QStringList arguments = QApplication::arguments();

    QString videoPath = "D:/Downloads/1.mp4";
    QString prefix = "videoPath=";
    QString prefix2 = "imagePath=";
    QString prefix3 = "outputPath=";

    for (int i = 0; i < arguments.size(); i++) {
        QString arg = arguments.at(i);
        if (arg.startsWith(prefix)) {
            videoPath = arg.right(arg.size() - prefix.size());
        }
        if (arg.startsWith(prefix2)) {
            importImage(arg.right(arg.size() - prefix2.size()));
        }
        if (arg.startsWith(prefix3)) {
            outputPath = arg.right(arg.size() - prefix3.size()).toStdString();
        }
    }

    video = cv::VideoCapture(videoPath.toStdString());
    updateVideo(video);
}


void VideoEditor::updateVideo(const cv::VideoCapture &video){
    ui->preview->updateVideo(video);

    int numberFrame = video.get(cv::CAP_PROP_FRAME_COUNT),
        fps = video.get(cv::CAP_PROP_FPS);

    this->fps = fps;

    ui->controlSlider->setRange(0, video.get(cv::CAP_PROP_FRAME_COUNT));
    ui->controlSlider->setTracking(true);

    ui->timeline->updateVideoLength((numberFrame + fps-1) / fps);
}


void VideoEditor::setupMenus() {
    imageFileTypes << ".jpg" << ".png" << ".gif" << ".svg";
    imageFileTypesFilter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    audioFileTypes << ".wmv";
    audioFileTypesFilter = "Waveform Audio (*.wmv)";

    ui->actionImport_Media->setShortcut(QKeySequence::Open);
    connect(ui->actionImport_Image, SIGNAL(triggered(bool)),
            this, SLOT(importImages()));
    connect(ui->actionImport_Audio, SIGNAL(triggered(bool)),
            this, SLOT(importAudios()));
    connect(ui->actionImport_Media, SIGNAL(triggered(bool)),
            this, SLOT(importMedia()));
    connect(ui->actionExport, &QAction::triggered,
            this, &VideoEditor::writeVideo);
}


void VideoEditor::setupWidgets() {
    thumbnailManager = new ThumbnailManager(ui->imgListWidget);
    audioManager = new AudioManager(ui->audioListWidget);
    connect(ui->blurButton, SIGNAL(clicked()),
            this, SLOT(blurImage()));
    connect(ui->imgListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            this, SLOT(appendImageToThumbnail(QListWidgetItem *)));
}


void VideoEditor::setupVideoPlayer() {
    // add signal to play video when clicking playButton
    connect(ui->playButton, SIGNAL(clicked()), ui->preview, SLOT(play()));

    // set up skipForward button
    ui->skipForward->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->skipForward->setToolTip(tr("Forward"));
    connect(ui->skipForward, SIGNAL(clicked()), ui->preview, SLOT(forward()));

    // set up skipBackward button
    ui->skipBackward->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->skipBackward->setToolTip(tr("Backward"));
    connect(ui->skipBackward, SIGNAL(clicked()), ui->preview, SLOT(backward()));

    // connect controlSlider with position
    connect(ui->controlSlider, &ProgressBar::sliderPressed,
            ui->preview, &VideoPlayer::sliderPressed);
    connect(ui->controlSlider, &ProgressBar::sliderReleased,
            ui->preview, &VideoPlayer::sliderReleased);
    connect(ui->controlSlider, &ProgressBar::frameChanged,
            this, &VideoEditor::updatePosition);

    // connect frameUpdated in preview to update position in this class
    connect(ui->preview, &VideoPlayer::timeUpdated,
            this, &VideoEditor::updateCurrentTime);

    // connect positionChanged in this class to slider and preview
    connect(this, &VideoEditor::positionChanged,
            ui->controlSlider, &ProgressBar::setValue);

    // connect timeInSecChanged with timeline and preview
    connect(this, &VideoEditor::currentTimeChanged,
            ui->preview, &VideoPlayer::updateCurrentTime);
    connect(this, &VideoEditor::currentTimeChanged,
            ui->timeline, &Timeline::updateIndicatorPosition);
    connect(ui->timeline, &Timeline::timeIndicatorChanged,
            this, &VideoEditor::updateCurrentTime);

    connect(ui->timeline, &Timeline::changeFrame,
            ui->preview, &VideoPlayer::updateFrame);

    // add label and playButton to preview
    ui->preview->setChild(ui->label,
                          ui->playButton);
}


void VideoEditor::importImages() {
    QStringList files = importFiles("Import Images", "/", imageFileTypesFilter);
    for (auto & file : files) {
        if (imageFileTypes.contains(file.right(4))) {
            importImage(file);
        }
    }
}


void VideoEditor::importAudios() {
    QStringList files = importFiles("Import Audios", "/", audioFileTypesFilter);
    for (auto & file : files) {
        if (audioFileTypes.contains(file.right(4))) {
            importAudio(file);
        }
    }
}


void VideoEditor::importImage(const QString& fileName) {
    img::Image image(fileName.toStdString());
    thumbnailManager->addImage(image, fileName);
}


void VideoEditor::importAudio(const QString& fileName) {
    audioManager->addAudio(fileName);
}


void VideoEditor::importMedia() {
    QString filter = imageFileTypesFilter + " ;; " + audioFileTypesFilter;
    QStringList files = importFiles("Import Media", "/", filter);

    for (auto & file : files) {
        if (imageFileTypes.contains(file.right(4))) {
            importImage(file);
        } else if (audioFileTypes.contains(file.right(4))) {
            importAudio(file);
        } else {
            qDebug() << "Invalid file:" << file;
        }
    }
}


QStringList VideoEditor::importFiles(const QString &caption, const QString &dir, const QString &filter) {
    QStringList files = QFileDialog::getOpenFileNames(this, caption, dir, filter);
    return files;
}


void VideoEditor::blurImage() {
    img::Image *image = ui->timeline->getImageAtIndicator();
    if (image == nullptr) return;
    image->blur(100, 100);

    emit imageChanged();
}


void VideoEditor::appendImageToThumbnail(QListWidgetItem* item) {
    Image *image = thumbnailManager->getImage(item);
    ui->timeline->addImageAtIndicator(image);
}


void VideoEditor::updatePosition(int position) {
    if (this->position != position) {
        this->position = position;
        this->timeInSec = 1.0 * position / fps;
        emit positionChanged(position);
        emit currentTimeChanged(timeInSec);
    }
}


void VideoEditor::updateCurrentTime(double time) {
    if (this->timeInSec != time) {
        this->timeInSec = time;
        this->position = int(time * fps);
        emit positionChanged(position);
        emit currentTimeChanged(timeInSec);
    }
}


VideoEditor::~VideoEditor() {
    delete ui;
}

void VideoEditor::writeVideo() {
    cv::VideoWriter outputVideo;
    cv::Size sizeFrame(640, 480);

    qDebug() << outputPath.c_str();

    remove(outputPath.c_str());
    bool isOk = outputVideo.open(outputPath.c_str(), cv::VideoWriter::fourcc('a', 'v', 'c', '1'), 30.0, sizeFrame, true);
    int length = 10 * fps;
    qDebug() << "start exporting" << isOk;
    for (int i = 0; i < length; i++){
        double time = 1.0 * i / fps;
        Image* image = ui->timeline->getImage(time);
        cv::Mat frame;
        video >> frame;
        if (image != nullptr) frame = image->getModifiedImg();
        cv::resize(frame, frame, sizeFrame);
        outputVideo << frame;
    }
    outputVideo.release();
    qDebug() << "end exporting";
}

