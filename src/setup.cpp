//
// Created by nhatv on 2 Jan 2022.
//

#include "videoeditor.h"
#include "ui_VideoEditor.h"

void VideoEditor::setupAudio() {
    audioManager = new AudioManager(ui->audioListWidget);
    audioPlayer = new AudioPlayer(audioManager, ui->timeline);

    connect(ui->audioListWidget, &QListWidget::itemDoubleClicked,
            this, &VideoEditor::appendAudioToThumbnail);
    connect(ui->preview, SIGNAL(playStateChanged(bool)),
            audioPlayer, SLOT(updatePlayState(bool)));
    connect(ui->timeline, SIGNAL(playStateChanged(bool)),
            audioPlayer, SLOT(handleIndicatorSignal(bool)));
    connect(ui->timeline, SIGNAL(seekAudioRequested(double)),
            audioPlayer, SLOT(seek(double)));

    connect(ui->preview, &VideoPlayer::seekAudioRequested,
            audioPlayer, &AudioPlayer::seek);
}

void VideoEditor::setupImage() {
    setupImageToolbar();

    imageManager = new ImageManager(ui->imgListWidget);
    connect(ui->imgListWidget, &QListWidget::itemDoubleClicked,
            this, &VideoEditor::appendImageToThumbnail);

    // setup animation
    connect(ui->timeline, &Timeline::animationApplied,
            this, &VideoEditor::applyAnimation);
    connect(ui->timeline, &Timeline::blurTypeApplied,
            this, &VideoEditor::applyBlur);

    // setup opencv fourcc
    QString os = QSysInfo::productType();
    if (os == "osx" || os == "macos") {
        fourcc = cv::VideoWriter::fourcc('a', 'v', 'c', '1');
    } else {
        fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    }
}

void VideoEditor::setupImageToolbar() {
    connect(ui->blurButton, &QToolButton::clicked,
            this, &VideoEditor::blurImage);
    connect(ui->resetButton, &QToolButton::clicked,
            this, &VideoEditor::resetImage);
    connect(ui->rotateButton, &QToolButton::clicked,
            this, &VideoEditor::rotateImageRight);

    // setup blurSlider
    blurSlider = new QSlider(Qt::Vertical);
    blurSlider->setWindowFlag(Qt::ToolTip);
    blurSlider->setVisible(false);
    blurSlider->setFixedSize(22, 200);
    blurSlider->setRange(0, 100);
    connect(blurSlider, &QSlider::valueChanged,
            this, &VideoEditor::updateBlurLevel);
}



void VideoEditor::setupMenus() {
    setupImports();
    connect(ui->actionExport, &QAction::triggered,
            this, &VideoEditor::writeVideo);
}

void VideoEditor::setupTimeline() {
    // setup images
    connect(ui->timeline, &Timeline::imageAdded,
            this, &VideoEditor::addImageToResultVideo);
    connect(ui->timeline, &Timeline::imageDeleted,
            this, &VideoEditor::deleteImageFromResultVideo);
    connect(ui->timeline, &Timeline::imageSelected,
            this, &VideoEditor::imageSelected);

    // setup time
    connect(this, &VideoEditor::currentTimeChanged,
            ui->timeline, &Timeline::updateIndicatorPosition);
    connect(ui->timeline, &Timeline::timeIndicatorChanged,
            this, &VideoEditor::updateCurrentTime);
}

void VideoEditor::setupVideoClass() {
    // create an instance of Video class
    resultVideo = new vid::Video(width, height, fps);
    ui->videoWindow->setSize(width, height);

    updateVideoLength(60);
}

void VideoEditor::setupVideoPlayer() {
    // add signal to play video when clicking playButton
    connect(ui->playButton, &QToolButton::clicked, ui->preview, &VideoPlayer::play);

    // set up skipForward button
    ui->skipForward->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->skipForward->setToolTip(tr("Forward"));
    connect(ui->skipForward, &QToolButton::clicked, ui->preview, &VideoPlayer::forward);

    // set up skipBackward button
    ui->skipBackward->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->skipBackward->setToolTip(tr("Backward"));
    connect(ui->skipBackward, &QToolButton::clicked, ui->preview, &VideoPlayer::backward);

    // connect controlSlider with position
    connect(ui->controlSlider, &ProgressBar::sliderPressed,
            ui->preview, &VideoPlayer::sliderPressed);
    connect(ui->controlSlider, &ProgressBar::sliderReleased,
            ui->preview, &VideoPlayer::sliderReleased);
    connect(ui->controlSlider, &ProgressBar::frameChanged,
            this, &VideoEditor::updatePosition);
    connect(this, &VideoEditor::positionChanged,
            ui->controlSlider, &ProgressBar::setValue);

    // connect time in preview and videoEditor
    connect(ui->preview, &VideoPlayer::timeUpdated,
            this, &VideoEditor::updateCurrentTime);
    connect(this, &VideoEditor::currentTimeChanged,
            ui->preview, &VideoPlayer::updateCurrentTime);

    // connect videoLengthChanged in timeline to videoEditor updateVideoLength
    connect(ui->timeline, &Timeline::videoLengthChanged,
            this, &VideoEditor::updateVideoLength);

    // connect changeFrame in VideoEditor with updateFrame VideoPlayer
    connect(this, &VideoEditor::changeFrame,
            ui->preview, &VideoPlayer::updateFrame);

    // add label and playButton to preview
    ui->preview->setChild(ui->videoWindow, ui->playButton);
}

void VideoEditor::setupWidgets() {
    setupAudio();
    setupImage();
    setupTimeline();
    setupVideoClass();
    setupVideoPlayer();
}