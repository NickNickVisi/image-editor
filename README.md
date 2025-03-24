# Image editor

A basic command line image editor written in C that supports various filters and actions on images.

This editor can handle P1, P2, P3, P4, P5 and P6 image files.

In order for the program to be compiled, the `make` command has to be executed in the root folder. Use `make clean` to remove object files if needed.

## Current supported commands and their usage

> - LOAD \<filename\> | loads an image from the given path into the program memory;
>
> - SELECT ALL | selects the whole image for further processing;
>
> - SELECT \<x1\> \<y1\> \<x2\> \<y2\> | selects given coordinates for processing;
>
> - HISTOGRAM \<stars\> \<bins\> | generates the histogram of the current loaded image, given a maximum number of stars and bins;
>
> - EQUALIZE | equalizes the image;
>
> - ROTATE \<x\> | rotates the image by *x* degrees anti-clockwise, negative values can be used for clockwise. *x* can only be a multiple of 90;
>
> - CROP | crops the current image selection;
>
> - APPLY \<FILTER_NAME\> | applies the given filter to the image;
>
>   - EDGE | applies the edge filter to the image;
>
>   - SHARPEN | sharpens the image;
>  
>   - BLUR | blurs the image;
>
>   - GAUSSIAN_BLUR | applies the gaussian blur;
>
> - SAVE \<filename\> | saves the image to the given path in a binary form;
>
> - SAVE \<filename\> ascii | saves the image to the given path in a human readable form;
>
> - EXIT | exits the programs and frees the memory allocated for the image.

##
If you are to come across any issues with the program, please let me know. Thank you!
