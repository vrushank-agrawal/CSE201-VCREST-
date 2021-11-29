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

//    connect(ui->controlSlider, &QSlider::valueChanged, this, &VideoEditor::setDisplayImage);
}

void VideoEditor::updateVideo(const cv::VideoCapture &video){
    ui->preview->updateVideo(video);

    ui->progressBar->setRange(0, video.get(cv::CAP_PROP_FRAME_COUNT));
    ui->progressBar->setTracking(true);
    ui->controlSlider->setTracking(true);
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

    // set signal update Slider to set value of progressBar
    connect(ui->preview, SIGNAL(updateSlider(int)), ui->progressBar, SLOT(setValue(int)));

    // add signal to change progressBar to change to correspond frame in preview
    connect(ui->progressBar, SIGNAL(sliderPressed()),
            ui->preview, SLOT(sliderPressed()));
    connect(ui->progressBar, SIGNAL(sliderMoved(int)),
            ui->preview, SLOT(sliderMoved(int)));
    connect(ui->progressBar, SIGNAL(sliderReleased()),
            ui->preview, SLOT(sliderReleased()));

    // add signal to change controlSlider to change to correspond frame in preview
    connect(ui->controlSlider, SIGNAL(sliderPressed()),
            ui->preview, SLOT(sliderPressed()));
    connect(ui->controlSlider, SIGNAL(sliderMoved(int)),
            ui->preview, SLOT(sliderMoved(int)));
    connect(ui->controlSlider, SIGNAL(sliderReleased()),
            ui->preview, SLOT(sliderReleased()));

    // adjust controlSlider and progressBar according to the other
    connect(ui->controlSlider, &QSlider::rangeChanged, ui->progressBar, &QSlider::setRange);
    connect(ui->progressBar, &QSlider::rangeChanged, ui->controlSlider, &QSlider::setRange);

    connect(ui->controlSlider, &QSlider::valueChanged, ui->progressBar, &QSlider::setValue);
    connect(ui->progressBar, &QSlider::valueChanged, ui->controlSlider, &QSlider::setValue);

    // add label, playButton and progressBar to preview
    ui->preview->setChild(ui->label,
                          ui->playButton);

    // add video to preview
    updateVideo(cv::VideoCapture("D:/Downloads/sample-mp4-file-small.mp4"));

}

void VideoEditor::importImage() {
    QString filter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    QString fileName = importFile("Import Image", "/", filter);
    img::Image image(fileName.toStdString());
    if (false)
        thumbnailManager->addImage(QPixmap(":/img-error.png"), fileName);
    else
        thumbnailManager->addImage(image.getModifiedImg(), fileName);
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

VideoEditor::~VideoEditor() {
    delete ui;
}

