## Collage
__Description__: subclass of the image, an object which has an array of subimages within.
### Capabilitities:
1. __TwoStitch__: Given an array of images, double stitches them based on their more dominant ratios. 
The dominant ratio is the maximum(maximum(width-height ratio, height-width ratio) for all images in the array) 
2. __ThreeStitch__: Double stitches two images first based on the dominant ratio and then calls another double stitch
on the product image to create the final image
3. __FourStitch__: double stitch two double stitches in similar manner as the ThreeStitch
4. __FourStitchRec__: Recursively fourstitches into a mega collage.

