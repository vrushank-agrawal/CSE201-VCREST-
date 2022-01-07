# GUI

## VideoEditor class

The main class to create the whole GUI by using subclasses: VideoPlayer, Timeline, ProgressBar, ImageManager, AudioPlayer and AudioManager.

__Utility__:
- Import Media files
- Export a video
- Receive and send signal to keep the time unified in classes: Timeline, AudioPlayer, VideoPlayer and ProgressBar
- Using Video class to simulate the video to preview as well as create animation
- Using Image class to modify the image like blurring, rotating

## VideoPlayer class

Class for creating a widget to display video by frames.

__Utility__:
- Has buttons to play/stop video, forward or backward 5 seconds.
- Using VideoWindow class to show frame by frame of the video.

## ProgessBar class

A slider to show the progress of the video in preview.

## Timeline class

A class to create the timeline.

__Utility__
- Adding AudioItem and ImageItem to create a video in the indicator (or after the last image/audio if the indicator already has an image/audio)
- Allowing moving or resizing (to change the duration) of Audio or Image
- Deleting the image/audio by double-clicking
- Have an indicator to show the current time in the timeline
- Allow jumping the indicator by double-clicking the time section

## ImageItem class

A class for the image in timeline

__Utility__
- Add/Delete image to the video
- Resizing image
- Have a menu by right click to the ImageItem to choose Animation of Blur type
- Having one selected ImageItem to apply effect such as blurring or rotating