# VEST - Video editing software tool

This is a unique video editing software developed to help a user create a video out of a group of images. The main feature is to allow the user to merge images with an audio file in a given sequence by analyzing the audio's bpm. Further features include adding simple animations to the corresponding video and certain filters to the images imported into the application by the user.


## Members (name surname, [role]   |  github username, trello username,)

* Vrushank Agrawal [project leader]                               | vrushank-agrawal, vrushank_agrawal
* Duy Nhat Vo, [git leader]                                       | nhat-vo, lavawolf
* Lucia Carai, [trello assistant]                                 | LuciaCarai, luciacarai
* Dimitri Korkotashvilli                                          | Dimitri-Korkotashvili, dkorkot
* Lasha Koroshinadze                                              | lashahub, lashakoroshinadze
* Hieu Le                                                         | Hieu-Lee, hieule203
* Minh Tung Nguyen                                                | minhtung0404, tungnguynminh2
* Minjoo Kim                                                      | minjoo-johanna, ---
* Hayate Sasaki                                                   | hayate0s, hayatesasaki
* Yufei Liu                                                       | elisabeth04, user24392150
* Yi Yao Tan                                                      | yao-creative, ---

## Teams

### GUI

* Duy Nhat Vo
* Hieu Le
* Minh Tung Nguyen
* Minjoo Kim

### Video processing and animations

* Dimitri Korkotashvilli
* Yufei Liu
* Lucia Carai

### Image processing and filters

* Vrushank Agrawal
* Yi Yao Tan

### Audio analyzing

* Lasha Koroshinadze
* Hayate Sasaki

## Third parties
- Qt6.2.1
- OpenCV 4.5.2

## Setting for CLion
- In Setting(Preferences)/Build, Execute and Deployment
    - Toolchain to change your compiler
    - In CMake: -DCMAKE_PREFIX_PATH=path/to/your/Qt (example ~/Qt/6.2.1/MacOS)

## Setup for OpenCV
### Windows
(All paths are written assuming QT and OpenCV are downloaded in the directory C:\ )
1. Download the latest version of OpenCV from `https://opencv.org/releases/`
2. Unpack the files in `C:\opencv` or a folder of your choice (path will then be different in the next steps)
3. Create a new folder release or any other name in the opencv folder `C:\opencv\release` 
4. Open CMake GUI (download here `https://cmake.org/download/`)
    - In "Where is the source code" put `C:\opencv\sources`
    - In "Where to build the binaries" put `C:\opencv\release` (or the folder as you named it) and click `configure`
    - Choose `Specify native compilers`
    - Change the generator of the project to `MinGW Makefiles` and Click `Next`
    - For C compiler browse to the Qt directory and chosse the gcc file in this path (example `C:\Qt\Tools\mingw810_64\bin\gcc.exe` )
    - For C++ choose the g++ file in the same folder ( example `C:\Qt\Tools\mingw810_64\bin\gpp.exe` )
    - After configuration is complete search for `WITH_QT` in the search bar and tick/check its value
    - Search for `CMAKE_BUILD_TYPE` and write `Release` for its value
    - Click on configure and after configuration click on `generate`
5. Now go to `C:\opencv\release\bin` and add this path to the environment variables 
6. Now add this path `C:\opencv\release\install\x64\mingw\bin`  or  `C:\opencv\release\install\x86\mingw\bin` to environment variables
7. If qt is not added to path then add this path to environment variables `C:\Qt\Tools\QtCreator\bin`
8. If mingw is not added to path then add this path to environment variables C:\Qt\6.2.1\mingw81_64\bin
9. Open Command prompt in the location `C:\opencv\release` by typing `cmd` in the address bar (at the top) of the window
10. In the command prompt (confirm the loaction is folder 'release' or 'the anem you gave it') type the command: `mingw32-make`
11. wait for the installtion to complete (takes a lot of time) 
12. Now try to run `src/testing_opencv` as a separate debug environment in CLion 

Note:
if there is no error and the image lena.jpg is displayed then OpenCV is successfully integrated, otherwise retry the entire process / try google

### MacOS
1. Getting OpenCV Source Code
    - Download OpenCV source code using this [link](https://github.com/opencv/opencv/archive/4.5.4.zip) and unpack it.
2. Building OpenCV from Source Using CMake
    - Create a temporary directory, which we denote as `build_opencv` inside `opencv-4.5.4` folder, where you want to put the generated Makefiles, project files as well the object files and output binaries and enter there.
    - Generate Makefile (2 ways)
      - Using terminal: Open terminal on folder `build_opencv` and run `cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON ../opencv` on terminal
      - Using cmake-gui
        - set the opencv source path
        - set the build path to `build_opencv`
        - set `CMAKE_BUILD_TYPE` to `Release`
        - set `BUILD_EXAMPLES` to `ON`
        - run `Configure`
        - run `Generate`
    - Build by run `make -j7` on terminal

Notes: 

Use Xcode g++ compiler because using other compiler leads to an error like `Undefined symbols for architecture arm64`. If you also have this problem you probably want to change to Xcode g++ compiler.
