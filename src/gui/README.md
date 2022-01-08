# GUI

## VideoEditor class `videoeditor.h`

The main class to create the whole GUI was by using the subclasses: `AudioPlayer`, `AudioManager`, `ImageManager`, `ProgressBar`, `Timeline`, and `VideoPlayer`.

__Functionalities__:
- Import Media files
- Export a video
- Receive and send signals to synchronize time in classes: `Timeline`, `AudioPlayer`, `VideoPlayer` and `ProgressBar`
- Using `vid::Video` class to simulate the video to preview as well as create animation
- Using `img::Image` class to modify the image like blurring, rotating



## List Manager classes

#### `AudioManager`class `audiomanager.h`

Allows importing audio files (`.mp3` or `.wav`) to the application

__Functionalities__
- Import and store audio files
- Bind each audio file to a separate `QMediaPlayer` for audio playing


#### `ImageManager`class `imagemanager.h`

Allows importing audio files (`.jpg`, `.png`, ...) to the application

__Functionalities__
- Import and store image files

## `AudioPlayer` class `audioplayer.h`

Manage audio playing

__Functionalities__
- Play / Pause the audio cues accordingly to the application's state
- Manages seeking and switching between audio cues
- Synchronized with the `Timeline`'s time


## `ProgressBar` class `progressbar.h`

A slider to show the progress of the video in preview.


## `Timeline` class `timeline.h`

A class to create the timeline.

__Functionalities__
- Adding AudioItem and ImageItem to create a video in the indicator (or after the last image/audio if the indicator already has an image/audio)
- Allowing moving or resizing (to change the duration) of Audio or Image
- Deleting the image/audio by double-clicking
- Have an indicator to show the current time in the timeline
- Allow jumping the indicator by double-clicking the time section

#### `AudioItem` class `audioitem.h`

A class for managing audio cues in `Timeline`

__Functionalities__
- Add/Remove audio cues to/from the video
- Resizing audio's duration


#### `ImageItem` class `imageitem.h`

A class for the image in timeline. Implementation is similar to `AudioItem`, but with additional functionalities

__Functionalities__
- Add/Delete images to the video
- Resize image's duration
- Right click for menu to choose Animation of Blur type
- Having one selected ImageItem to apply effect such as blurring or rotating


## VideoPlayer class `videoplayer.h`

Class for creating a widget to display video by frames.

__Functionalities__:
- Has buttons to play/pause video, forward or backward 5 seconds.
- Uses `VideoWindow` class to show frame by frame of the video.