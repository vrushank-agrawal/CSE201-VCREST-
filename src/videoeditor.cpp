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
    setupVideoClass();
    setupVideoPlayer();
    setupMenus();
    setupWidgets();

    // add video to preview
    QStringList arguments = QApplication::arguments();
    QString prefix2 = "imagePath=";

    for (const auto& arg : arguments) {
        if (arg.startsWith(prefix2)) {
            importImage(arg.right(arg.size() - prefix2.size()));
        }
    }
}

void VideoEditor::setupVideoClass() {
    // create an instance of Video class
    resultVideo = new vid::Video(640, 360, fps);

    ui->controlSlider->setRange(0, numberFrame);
    ui->controlSlider->setTracking(true);

    ui->timeline->updateVideoLength((numberFrame + fps-1) / fps);
}


void VideoEditor::setupMenus() {
    imageFileTypes << ".jpg" << ".png" << ".gif" << ".svg";
    imageFileTypesFilter = "JPG Image (*.jpg) ;; PNG Image (*.png) ;; GIF Image (*.gif) ;; SVG Image (*.svg)";
    audioFileTypes << ".wmv";
    audioFileTypesFilter = "Waveform Audio (*.wmv)";

    ui->actionImport_Media->setShortcut(QKeySequence::Open);
    ui->actionExport->setShortcut(QKeySequence::Save);
    connect(ui->actionImport_Image, SIGNAL(triggered(bool)),
            this, SLOT(importImages()));
    connect(ui->actionImport_Audio, SIGNAL(triggered(bool)),
            this, SLOT(importAudios()));
    connect(ui->actionImport_Media, SIGNAL(triggered(bool)),
            this, SLOT(importMedia()));
    connect(ui->actionExport, &QAction::triggered,
            this, &VideoEditor::writeVideo);

    QString os = QSysInfo::productType();
    if (os == "osx" || os == "macos") {
        fourcc = cv::VideoWriter::fourcc('a', 'v', 'c', '1');
    } else {
        fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    }
}


void VideoEditor::setupWidgets() {
    thumbnailManager = new ThumbnailManager(ui->imgListWidget);
    audioManager = new AudioManager(ui->audioListWidget);
    connect(ui->blurButton, &QToolButton::clicked,
            this, &VideoEditor::blurImage);
    connect(ui->imgListWidget, &QListWidget::itemDoubleClicked,
            this, &VideoEditor::appendImageToThumbnail);
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

    connect(ui->timeline, &Timeline::imageAdded,
            this, &VideoEditor::addImageToResultVideo);
    connect(ui->timeline, &Timeline::imageDeleted,
            this, &VideoEditor::deleteImageFromResultVideo);

    // connect changeFrame in VideoEditor with updateFrame VideoPlayer
    connect(this, &VideoEditor::changeFrame,
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
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    imageItem->image->blur(100, 100);
    imageItem->update();

    emit imageChanged();
}


void VideoEditor::appendImageToThumbnail(QListWidgetItem* item) {
    auto *image = new img::Image(thumbnailManager->getImage(item)->getMat());
    ui->timeline->addImageAtIndicator(image);
}


void VideoEditor::addImageToResultVideo(img::Image *image, double startTime, double duration) {
    resultVideo->addImage(image, startTime, duration);
}


void VideoEditor::deleteImageFromResultVideo(img::Image *image) {
    resultVideo->deleteImage(image);
}


void VideoEditor::updatePosition(int newPosition) {
    if (this->position != newPosition) {
        this->position = newPosition;
        this->timeInSec = 1.0 * newPosition / fps;
        emit positionChanged(newPosition);
        emit currentTimeChanged(timeInSec);
    }
}


void VideoEditor::updateCurrentTime(double time) {
    if (this->timeInSec != time) {
        cv::Mat frame = resultVideo->getMatByTime(time);
        emit changeFrame(frame);

        this->timeInSec = time;
        this->position = int(time * fps);
        emit positionChanged(position);
        emit currentTimeChanged(timeInSec);
    }
}


VideoEditor::~VideoEditor() {
    delete ui;
    delete resultVideo;
}

void VideoEditor::writeVideo() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilter("MP4 video (*.mp4)");
    std::string outputPath;
    if (dialog.exec()) {
        QString qOutputPath = dialog.selectedFiles()[0];
        if (qOutputPath.right(4) != ".mp4")
            qOutputPath.append(".mp4");
        outputPath = qOutputPath.toStdString();
    } else {
        return;
    }

    remove(outputPath.c_str());

    if (!resultVideo->writeVideo(outputPath, fourcc)) {
        QMessageBox errorMsg;
        errorMsg.setWindowTitle("Error");
        errorMsg.setText("Export is not supported on this platform");
        errorMsg.exec();
    }
}

