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
    ui->actionImport_Image->setShortcut(QKeySequence::Open);
    connect(ui->actionImport_Image, &QAction::triggered, this, &VideoEditor::importImage);

    connect(ui->actionImport_Audio, &QAction::triggered, this, &VideoEditor::importImage);
}

void VideoEditor::setupWidgets() {
    thumbnailManager = new ThumbnailManager(ui->imgListWidget);
    audioManager = new AudioManager(ui->audioListWidget);

    // testing
    setupImageListWidget();
    audioManager->addAudio("hello.mp3");
    audioManager->addAudio("world.mp3");
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
    QString filter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    QString fileName = importFile("Import Image", "/", filter);
    img::Image image(fileName.toStdString());
    if (false)
        thumbnailManager->addImage(QPixmap(":/img-error.png"), fileName);
    else {
        thumbnailManager->addImage(image, fileName);
        ui->timeline->addImage(thumbnailManager->getImage(0), QPointF(0, 5));
    }
}

void VideoEditor::importAudio() {

}

QString VideoEditor::importFile(const QString& caption, const QString& dir, const QString& filter) {
    QString fileName = QFileDialog::getOpenFileName(this, caption, dir, filter);
    return fileName;
}


void VideoEditor::setupImageListWidget() {
    auto *testPixmap = new QPixmap(":/img-error.png");

    thumbnailManager->addImage(*testPixmap, "test1");
    thumbnailManager->addImage(*testPixmap, "test2");
    thumbnailManager->addImage(*testPixmap, "test2222222222222222222222222222222222222222222");

    for (int i = 3; i < 10; i++) {
        thumbnailManager->addImage(*testPixmap, "test" + QString::number(i));
    }

    thumbnailManager->addImage(*testPixmap, QString::number(thumbnailManager->getImagesCount()));
}

void VideoEditor::setDisplayImage() {
    if (images.empty()) {
        imageIndex = -1;
    }
    else {
        double ratio = ((double)ui->controlSlider->value())/100.0;
        ratio *= images.size();
        imageIndex = (int) ratio;
        imageIndex = (imageIndex == images.size()) ? imageIndex - 1 : imageIndex;
    }
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

