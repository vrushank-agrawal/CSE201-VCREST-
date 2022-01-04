//
// Created by Minh Tung Nguyen on 03/12/2021.
//

#ifndef VIDEO_EDITOR_BX23_TIMELINE_H
#define VIDEO_EDITOR_BX23_TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QResizeEvent>
#include <QListWidgetItem>
#include <audioitem.h>
#include "Audio.hpp"
#include "imageitem.h"
#include "indicator.h"
#include "image.h"

class Timeline: public QGraphicsView {
Q_OBJECT

/*###################
 *      GENERIC
 ####################*/

public:
    explicit Timeline(QWidget *parent = 0);
    ~Timeline();
    static double default_image_length, default_audio_length;

    void updateVideoLength(int length);



private:
    Indicator *indicator = nullptr;
    QGraphicsScene *scene = nullptr;
    QGraphicsItem* separatorLine[2] = {nullptr, nullptr};

    qreal currentXPosition = 0;
    int lengthInSecond = 0;
    int sceneWidth = 120, sceneHeight = 120;
    qreal sceneShowingWidth = 3000;
    int timeHeight = 20;
    int xTimeOffset = 100, yTime = 0;

    enum TimelineMoveOption{
        KeepCurrentPosition,
        CenterIndicator,
    };

    void moveTimeline(TimelineMoveOption option);


signals:
    void playStateChanged(bool isPlaying);
    void timeIndicatorChanged(qreal time);
    void videoLengthChanged(int length);


public slots:
    void updateIndicatorPosition(double);


protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void wheelEvent(QWheelEvent *event);



/*###################
 *      AUDIO
 ####################*/

public:
    void addAudio(audio::Audio* audio, QString displayName, double sourceLength, double start, double end);
    void addAudioAtIndicator(audio::Audio* audio, QString displayName, double sourceLength, double max_length = default_audio_length);
    void appendAudio(audio::Audio* audio, QString displayName, double sourceLength, double length=default_audio_length);
    audio::Audio* getAudio(qreal time);
    AudioItem* getAudioItem(double time);
    double getAudioStartTime(double time);

private:
    QMultiMap<double, AudioItem*> audioMap;

    QMultiMap<double, AudioItem*>::iterator getAudioIterator(double time);
    void setAudioItemPosition(AudioItem *item, double startTime, double endTime);


signals:
    void audioAdded(audio::Audio *audio, double startTime, double duration);
    void audioDeleted(audio::Audio *audio);
    void seekAudioRequested(double time);


private slots:
    void deleteAudio(AudioItem*);
    void moveAudioItem(AudioItem *item, double startPos, double endPos);
    void updateAudioPosition(AudioItem* item, double start, double end);
    void resizeAudioItem(AudioItem *item, double newLength);



/*###################
 *      IMAGE
 ####################*/

public:
    void addImage(img::Image *image, double start, double end); // add an Image at the specified location
    void addImageAtIndicator(img::Image *image, double max_length = default_image_length); // call appendImage if an image already exists
    void appendImage(img::Image *image, double length=default_image_length); // append an Image to the end of the timeline
    img::Image* getImage(qreal time);


private:
    QMultiMap<double, ImageItem*> imageMap;

    ImageItem* getImageItem(double time);
    void setImageItemPosition(ImageItem *item, double startTime, double endTime);


signals:
    void animationApplied(img::Image *image, vid::Animation animation);
    void blurTypeApplied(ImageItem *imageItem);
    void imageAdded(img::Image *image, double startTime, double duration, vid::Animation animation);
    void imageDeleted(img::Image *image);
    void imageSelected();


private slots:
    void moveImageItem(ImageItem *item, double startPos, double endPos);
    void updateTime(qreal xPosition);
    void updateImagePosition(ImageItem* item, double start, double end);
    void resizeImageItem(ImageItem *item, double newLength);
    void deleteImage(ImageItem*);
};

#endif //VIDEO_EDITOR_BX23_TIMELINE_H
