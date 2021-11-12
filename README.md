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
    - Download the latest version of OpenCV from https://opencv.org/releases/
    - Unpack the files in C:\opencv or a folder of your choice (path will then be different in the next steps)
    - Create a new folder release or any other name in the opencv folder C:\opencv\release 
    - Open CMake GUI (download here https://cmake.org/download/)
        - In "Where is the source code" put C:\opencv\sources
        - In "Where to build the binaries" put C:\opencv\release (or the folder as you named it)
        - click configure
        - Choose 'Specify native compilers'
        - Change the generator of the project to "MinGW Makefiles"
        - Click Next
        - For C compiler browse to the Qt directory and chosse the gcc file in this path (example C:\Qt\Tools\mingw810_64\bin\gcc.exe )
        - For C++ choose the g++ file in the same folder ( example C:\Qt\Tools\mingw810_64\bin\gpp.exe )
        - After configuration is complete search for "WITH_QT" in the search bar and tick/check its value
        - Search for "CMAKE_BUILD_TYPE" and write 'Release' for its value
        - Click on configure and after configuration click on "generate"
    - Now go to C:\opencv\release\bin and add this path to the environment variables 
    - Now add this path C:\opencv\release\install\x64\mingw\bin  or  C:\opencv\release\install\x86\mingw\bin to environment variables
    - If qt is not added to path then add this path to environment variables C:\Qt\Tools\QtCreator\bin
    - If mingw is not added to path then add this path to environment variables C:\Qt\6.2.1\mingw81_64\bin
    - Open Command prompt in the location C:\opencv\release by typing 'cmd' in the address bar (at the top) of the window
    - In the command prompt (confirm the loaction is folder 'release' or 'whatever you named it') type the command: mingw32-make
    - wait for the installtion to complete (takes a lot of time) 
    - Now try to run src/testing_opencv as a separate debug environment in CLion 
    - if there is no error and the image lena.jpg is displayed then OpenCV is successfully integrated, otherwise retry the entire process or try google or contact me at vrushank2001@gmail.com
