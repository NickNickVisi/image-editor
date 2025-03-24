#ifndef __image_structs__
    #define __image_structs__

	// Structure for the image with 3 colour channels
	typedef struct {
		unsigned char r, g, b;
	} channels_3;

	// Structure for the image with either one channel or three channels
	typedef struct {
		int height, width, thresh;
		char format[3];
		unsigned char **matrix1;
		channels_3 **matrix3;
	} image;

	// Structure for the selection of pixels in the image
	typedef struct {
		int x1, y1, x2, y2;
	} selection;

#endif
