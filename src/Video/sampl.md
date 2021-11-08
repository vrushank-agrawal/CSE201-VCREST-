img[] //array of images which is shared
//receives indexes of images and time slots for each image and constructs a simple video
// creates the video
receive(time[], indexes[]);

//function which zooms the image randomly depending on time interval
zoom(img, time_interval);

//function which rotates the image with respect to the centre(in time)
rotate(img, time_interval);


//function receives image and pixel coordinates and some zoom coefficient, depending on which it makes zooms the image
zoom_img(img, coordinate, ratio);

//rotates img with respect to the angle and a pixel coordinate
rotate_img(img, coordinate,  angle);
