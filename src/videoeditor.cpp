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
    setupAudio();

    // add video to preview
    QStringList arguments = QApplication::arguments();
    QString prefix = "audioPath=";
    QString prefix2 = "imagePath=";

    for (const auto& arg : arguments) {
        if (arg.startsWith(prefix)) {
            importAudio(arg.right(arg.size() - prefix2.size()));
        }
        if (arg.startsWith(prefix2)) {
            importImage(arg.right(arg.size() - prefix2.size()));
        }
    }
}

VideoEditor::~VideoEditor() {
    delete ui;
    delete resultVideo;
    delete thumbnailManager;
    delete audioManager;
}

/*###################
*      SETUP
####################*/

void VideoEditor::setupVideoClass() {
    // create an instance of Video class
    resultVideo = new vid::Video(width, height, fps);
    ui->videoWindow->setSize(width, height);

    ui->controlSlider->setRange(0, numberFrame);
    ui->controlSlider->setTracking(true);

    ui->timeline->updateVideoLength((numberFrame + fps-1) / fps);
}

void VideoEditor::setupMenus() {
    imageFileTypes << ".jpg" << ".png" << ".gif" << ".svg";
    imageFileTypesFilter = "Images (*.jpg *.png *.gif *.svg)";
    audioFileTypes << ".wmv" << ".mp3";
    audioFileTypesFilter = "Audio (*.wmv *.mp3)";

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
    audioPlayer = new AudioPlayer(audioManager, ui->timeline);
    connect(ui->blurButton, &QToolButton::clicked,
            this, &VideoEditor::blurImage);
    connect(ui->resetButton, &QToolButton::clicked,
            this, &VideoEditor::resetImage);
    connect(ui->imgListWidget, &QListWidget::itemDoubleClicked,
            this, &VideoEditor::appendImageToThumbnail);
    connect(ui->audioListWidget, &QListWidget::itemDoubleClicked,
            this, &VideoEditor::appendAudioToThumbnail);
    connect(ui->preview, SIGNAL(playStateUpdated(bool)),
            audioPlayer, SLOT(updatePlayState(bool)));
    connect(ui->timeline, SIGNAL(playStateChanged(bool)),
            audioPlayer, SLOT(handleIndicatorSignal(bool)));
    connect(ui->timeline, SIGNAL(seekAudioRequested(double)),
            audioPlayer, SLOT(seek(double)));

//    QMediaPlayer *player1 = new QMediaPlayer;
//    QMediaPlayer *player2 = new QMediaPlayer;
//    QAudioOutput *output1 = new QAudioOutput;
//    QAudioOutput *output2 = new QAudioOutput;
//    player1->setAudioOutput(output1);
//    player2->setAudioOutput(output2);
//    player1->setSource(QUrl("D:/Downloads/mp3_ex.mp3"));
//    player2->setSource(QUrl("../media/audio/test.mp3"));
//    player1->play();
//    player2->play();
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

    // connect blurLevelChanged in this class to slider
    blurSlider = new QSlider(Qt::Vertical);
    blurSlider->setWindowFlag(Qt::ToolTip);
    blurSlider->setVisible(false);
    blurSlider->setFixedSize(22, 200);
    blurSlider->setRange(1, 100);
    connect(blurSlider, &QSlider::valueChanged,
            this, &VideoEditor::updateBlurLevel);

    connect(ui->rotateButton, &QToolButton::clicked,
            this, &VideoEditor::rotateImageRight);

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
    connect(ui->timeline, &Timeline::imageSelected,
            this, &VideoEditor::imageSelected);

    // connect changeFrame in VideoEditor with updateFrame VideoPlayer
    connect(this, &VideoEditor::changeFrame,
            ui->preview, &VideoPlayer::updateFrame);

    // connect animationApplied to apply animation
    connect(ui->timeline, &Timeline::animationApplied,
            this, &VideoEditor::applyAnimation);

    // add label and playButton to preview
    ui->preview->setChild(ui->videoWindow,
                          ui->playButton);
}

void VideoEditor::setupAudio() {
}





/*###################
*     IMPORT
####################*/

void VideoEditor::importAudio(const QString& fileName) {
    audioManager->addAudio(fileName);
}

void VideoEditor::importAudios() {
    QStringList files = importFiles("Import Audios", "/", audioFileTypesFilter);
    for (auto & file : files) {
        if (audioFileTypes.contains(file.right(4))) {
            importAudio(file);
        }
    }
}

QStringList VideoEditor::importFiles(const QString &caption, const QString &dir, const QString &filter) {
    QStringList files = QFileDialog::getOpenFileNames(this, caption, dir, filter);
    return files;
}

void VideoEditor::importImage(const QString& fileName) {
    img::Image image(fileName.toStdString());
    thumbnailManager->addImage(image, fileName);
}

void VideoEditor::importImages() {
    QStringList files = importFiles("Import Images", "/", imageFileTypesFilter);
    for (auto & file : files) {
        if (imageFileTypes.contains(file.right(4))) {
            importImage(file);
        }
    }
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

void VideoEditor::blurImage() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (blurSlider->isVisible()) {
        blurSlider->setVisible(false);
        return;
    }
    QPoint pos = ui->blurButton->mapToGlobal(QPoint(0, 0));
    blurSlider->move(pos.x()-blurSlider->width(), pos.y());
    blurSlider->setVisible(true);
    if (imageItem == nullptr) return;
    imageItem->image->blur(imageItem->blurLevel, imageItem->blurLevel);
    imageItem->update();
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::rotateImageRight() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    imageItem->image->rotateImgFit(-90.0);
    imageItem->update();
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::updateBlurLevel() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    imageItem->blurLevel = blurSlider->value();
    imageItem->unblurImage();
    imageItem->image->blur(imageItem->blurLevel, imageItem->blurLevel);
    imageItem->update();
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::resetImage() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    imageItem->resetImage();
    imageItem->update();
    imageItem->blurLevel = 1;
    blurSlider->setValue(1);
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}





/*###################
*      GENERIC
####################*/

void VideoEditor::updateCurrentTime(double time) {
    if (this->timeInSec != time) {
        if (time * fps > numberFrame) {
            time = 1.0 * numberFrame / fps;
            ui->playButton->clicked();
        }

        this->timeInSec = time;
        this->position = int(time * fps);
        updateFrame();
        emit positionChanged(position);
        emit currentTimeChanged(timeInSec);
    }
}

void VideoEditor::updatePosition(int newPosition) {
    updateCurrentTime(1.0 * newPosition / fps);
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




/*###################
*       AUDIO
####################*/

void VideoEditor::appendAudioToThumbnail(QListWidgetItem *item) {
    QString *source = audioManager->getAudio(item);
    QMediaPlayer *player = audioManager->getPlayer(*source);
    ui->timeline->addAudioAtIndicator(*source, player->duration());
}


/*###################
*       IMAGE
####################*/

void VideoEditor::appendImageToThumbnail(QListWidgetItem* item) {
    auto *image = new img::Image(thumbnailManager->getImage(item)->getMat());
    ui->timeline->addImageAtIndicator(image);
}

void VideoEditor::applyAnimation(img::Image *image, vid::Animation animation) {
    resultVideo->applyAnimation(image, animation);
}

void VideoEditor::addImageToResultVideo(img::Image *image, double startTime, double duration, vid::Animation animation) {
    resultVideo->addImage(image, startTime, duration);
    resultVideo->applyAnimation(image, animation);
    updateFrame();
}

void VideoEditor::deleteImageFromResultVideo(img::Image *image) {
    resultVideo->deleteImage(image);
    updateFrame();
}

void VideoEditor::imageSelected() {
    ImageItem *imageItem = ImageItem::getSelectedImageItem();
    if (imageItem == nullptr) return;
    blurSlider->setValue(imageItem->blurLevel);
    cv::Mat frame = resultVideo->getMatByTime(imageItem->getTimeOfFrame());
    emit changeFrame(frame);
}

void VideoEditor::updateFrame() {
    cv::Mat frame = resultVideo->getMatByTime(timeInSec);
    emit changeFrame(frame);
}
