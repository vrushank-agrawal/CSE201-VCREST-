## Functionalities

The project aims to provide the user with a unique feature of automatically creating a video with custom images in a given audio file.
- A user will import an audio file and a set of custom images.
- A function in the program will analyze the audio file using FFT's and recognize the its bpm, troughs and peaks in the audio file.
- Another function will automatically organize these images (randomly or with user preference) and combine them with the audio to create a video.
- There will be additional simple animations and filters that can be added in the video for effects.
- The user will also be provided with the ability to rearrange these images and animations in the video in the GUI manually.

END RESULT - You create a video of memories automatically with the tempo of a certain song for the right vibes!

## Deadlines and deliverables

### WEEK 2
- functions for adding filters and animations in the image and video parts
- determining audio library to implement

### WEEK 4
- Simple working GUI that previews the audio and the image files.
- Function to analyze the audio file returns valid values for image and video processing.
- A basic video can be made out of the imported images and audios.

### WEEK 6
- Integration of the animations, filters, and audio processing functions to smoothly run with the GUI
- GUI will have manual editing ability for the user to manually edit images and animations for a more unique and personal video.

### Week 8
- Integration of all poles into one branch
- Scan code for potential bugs and fix them

## Software Architecture
- How are you sub-dividing your project? 
    - The project is divided into mainly 5 namespaces
        - Audio
        - Export
        - GUI
        - Image
        - Video
    - All of these namespaces are contained in separate folders in `src` and accessible to each other through header files and CMake
    - These classes have several subclasses that are needed to organise the code structure
    - Details about the subclasses are documented inside the src folder for each pole

- What external dependencies do you have? Why?
    - QT 6.2.2
        - Contains all main libraries required to build the entire application.
    - QT Multimedia
        - Required to import, display, and play audio files in the GUI
    - minGW 9.0.0
        - Compiler required for the project to support QT libraries
    - OpenCV
        - Used for image and video manipulation
    - FFmpeg
        - Required for exporting functions
    - Audio Libraries
        - These are already imported and integrated in the code required for analyzing audio
- CMake
    - CMake calls the QT libraries and OpenCV as Interfaces from a separate folder
    - This organizes the code to reduces redundancy
    - All directories have separate CMake files that can are appended as subdirectories
