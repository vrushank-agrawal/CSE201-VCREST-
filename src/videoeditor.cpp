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
    connect(ui->controlSlider, SIGNAL(sliderPressed()),
            ui->preview, SLOT(sliderPressed()));
    connect(ui->controlSlider, SIGNAL(sliderReleased()),
            ui->preview, SLOT(sliderReleased()));
    connect(ui->controlSlider, SIGNAL(frameChanged(int)),
            this, SLOT(updatePosition(int)));

    // connect frameUpdated in preview to update position in this class
    connect(ui->preview, SIGNAL(frameUpdated(int)),
            this, SLOT(updatePosition(int)));

    // connect positionChanged in this class to slider and preview
    connect(this, SIGNAL(positionChanged(int)),
            ui->controlSlider, SLOT(setValue(int)));
    connect(this, SIGNAL(positionChanged(int)),
            ui->preview, SLOT(updateFrame(int)));

    // connect timeInSecChanged with
    connect(this, SIGNAL(timeIndicatorChanged(double)),
            ui->timeline, SLOT(updateIndicatorPosition(double)));
    connect(ui->timeline, SIGNAL(timeIndicatorChanged(qreal)),
            this, SLOT(updateTimeIndicator(double)));

    // add label and playButton to preview
    ui->preview->setChild(ui->label,
                          ui->playButton);

    // add video to preview
    QStringList arguments = QApplication::arguments();

    QString videoPath = "D:/Downloads/1.mp4";
    QString prefix = "videoPath=";

    for (int i = 0; i < arguments.size(); i++) {
        QString arg = arguments.at(i);
        if (arg.startsWith(prefix)) {
            videoPath = arg.right(arg.size() - prefix.size());
        }
    }

    updateVideo(cv::VideoCapture(videoPath.toStdString()));
}


void VideoEditor::importImage() {
    QString fileName = importFile("Import Image", "/", imageFileTypesFilter);
    importImage(fileName);
}


void VideoEditor::importImages() {
    QStringList files = importFiles("Import Images", "/", imageFileTypesFilter);
    for (auto & file : files) {
        if (imageFileTypes.contains(file.right(4))) {
            importImage(file);
        }
    }
}


void VideoEditor::importAudio() {
    QString fileName = importFile("Import Audio", "/", audioFileTypesFilter);
    importAudio(fileName);
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


QString VideoEditor::importFile(const QString& caption, const QString& dir, const QString& filter) {
    QString fileName = QFileDialog::getOpenFileName(this, caption, dir, filter);
    return fileName;
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
        emit timeIndicatorChanged(timeInSec);
    }
}


void VideoEditor::updateTimeIndicator(double time) {
    if (this->timeInSec != time) {
        this->timeInSec = time;
        this->position = int(time * fps);
        emit positionChanged(position);
        emit timeIndicatorChanged(timeInSec);
    }
}


VideoEditor::~VideoEditor() {
    delete ui;
}

