## General Note
This folder contains all the source code for the software. 
Each individual part of the project can be found in their respective folders.
The target files for CMake in this directory is `audio.cpp`, `export.cpp`, `image.cpp`, `import.cpp`, `setup.cpp`, and `videoeditor.cpp`.
These files call and set the base functions to be further called in the gui folder.
Here, CMake also calls and loads the subdirectories gui, image, audio, video, and export, 
details for which are explained in the corresponding folders.