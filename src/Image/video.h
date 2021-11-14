// Draft for video class

#ifndef OPENCV
#define OPENCV

#include <opencv2/opencv.hpp>
#include <iostream>
#endif //OPENCV

using namespace cv;
using namespace std;

#ifndef VIDEO_CLASS
#define VIDEO_CLASS

namespace vid {

    class Video {

     
        string filename_audio;
        list filenames_images;
        int time_of_display; 


    public:

        Video(list filenames_images, string filename_audio, int time_of_display; 
);

        ~Video();

      

        // returns true if input video is of valid format
        bool validVid(const string & 	filename_audio, const list &   filenames_images);


        // saves video in a certain file format
        bool saveVid();

        // Basic functions

        void cropVid();
        void resizeVid();
       

    };
}


#endif // VIDEO_CLASS