#include "../include/image.h"
#include "../include/tools.h"

// Deallocation of the memory used by the image, depending on the format
void deallocate(image *img)
{
	if (!img) {
		return;
	}
	if (img->format[1] != '3' && img->format[1] != '6') {
		dealloc_matrix1(img->matrix1, img->height);
	} else {
		dealloc_matrix3(img->matrix3, img->height);
	}
	free(img);
}

// Checks if the selection is a square
int issquare(int x1, int y1, int x2, int y2)
{
	return (x2 - x1 == y2 - y1);
}

// Verifies if the selection is the whole image
int original_coords(int x1, int y1, int x2, int y2, image *img)
{
	if (x1 && y1) {
		return 0;
	}
	if (x2 != img->width && y2 != img->height) {
		return 0;
	}
	return 1;
}

// Checks the validity of the coordinates
int check_cords(int x1, int y1, int x2, int y2, int width, int height)
{
	if (x1 < 0 || x1 > width || x2 < 0 || x2 > width) {
		printf("Invalid set of coordinates\n");
		return 0;
	}
	if (y1 < 0 || y1 > height || y2 < 0 || y2 > height) {
		printf("Invalid set of coordinates\n");
		return 0;
	}
	if (x1 == x2 || y1 == y2) {
		printf("Invalid set of coordinates\n");
		return 0;
	}
	printf("Selected %d %d %d %d\n", x1, y1, x2, y2);
	return 1;
}

// Checks the angle of rotation
int check_angle(int angle)
{
	if (angle < 0) {
		angle = -angle;
	}
	if (angle % 90 || angle > 360) {
		printf("Unsupported rotation angle\n");
		return 0;
	}
	return 1;
}

// Swaps two integer variables
void swap(int *x, int *y)
{
	int aux = *x;
	*x = *y;
	*y = aux;
}

// Sets the value to min or max if it is outside the interval
int clamp2(int x, int min, int max)
{
	if (x < min) {
		return min;
	}
	if (x > max) {
		return max;
	}
	return x;
}

// Rotates the selection of pixels in the image by 90 degrees to the right
void rotate_90select(image *img, selection *sel)
{
	int i, j, x, y;
	int height = sel->y2 - sel->y1;
	int width = sel->x2 - sel->x1;

	if (img->format[1] == '3' || img->format[1] == '6') {
		channels_3 **new_matrix = allocate_triple(height, width);

		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				x = sel->x1 + i;
				y = sel->y1 + j;
				if (x >= 0 && x < img->height && y >= 0 && y < img->width) {
					new_matrix[j][height - i - 1] = img->matrix3[x][y];
				}
			}
		}
		for (i = 0; i < width; i++) {
			for (j = 0; j < height; j++) {
				x = sel->x1 + i;
				y = sel->y1 + j;
				if (x >= 0 && x < img->height && y >= 0 && y < img->width) {
					img->matrix3[x][y] = new_matrix[i][j];
				}
			}
		}
		dealloc_matrix3(new_matrix, height);
	} else {
		unsigned char **new_matrix = allocate_single(height, width);

		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				x = sel->x1 + i;
				y = sel->y1 + j;
				if (x >= 0 && x < img->height && y >= 0 && y < img->width) {
					new_matrix[j][height - i - 1] = img->matrix1[x][y];
				}
			}
		}
		for (i = 0; i < width; i++) {
			for (j = 0; j < height; j++) {
				x = sel->x1 + i;
				y = sel->y1 + j;
				if (x >= 0 && x < img->height && y >= 0 && y < img->width) {
					img->matrix1[x][y] = new_matrix[i][j];
				}
			}
		}
		dealloc_matrix1(new_matrix, height);
	}
}

// Rotates the image 90 degrees to the right
void rotate_90all(image *img)
{
	int i, j;
	int height = img->height;
	int width = img->width;

	if (img->format[1] == '3' || img->format[1] == '6') {
		channels_3 **new_matrix = allocate_triple(height, width);

		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				new_matrix[j][height - i - 1] = img->matrix3[i][j];
			}
		}
		dealloc_matrix3(img->matrix3, height);
		swap(&img->height, &img->width);
		img->matrix3 = allocate_triple(img->width, img->height);
		for (i = 0; i < img->height; i++) {
			for (j = 0; j < img->width; j++) {
				img->matrix3[i][j] = new_matrix[i][j];
			}
		}
		dealloc_matrix3(new_matrix, img->height);
	} else {
		unsigned char **new_matrix = allocate_single(height, width);

		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				new_matrix[j][height - i - 1] = img->matrix1[i][j];
			}
		}
		dealloc_matrix1(img->matrix1, height);
		swap(&img->height, &img->width);
		img->matrix1 = allocate_single(img->width, img->height);
		for (i = 0; i < img->height; i++) {
			for (j = 0; j < img->width; j++) {
				img->matrix1[i][j] = new_matrix[i][j];
			}
		}
		dealloc_matrix1(new_matrix, img->height);
	}
}

// Rotates the image 180 degrees to the right
void rotate_180all(image *img)
{
	rotate_90all(img);
	rotate_90all(img);
}

// Rotates the image selection 180 degrees to the right
void rotate_180select(image *img, selection *sel)
{
	rotate_90select(img, sel);
	swap(&sel->x1, &sel->y1);
	swap(&sel->x2, &sel->y2);
	rotate_90select(img, sel);
	swap(&sel->x1, &sel->y1);
	swap(&sel->x2, &sel->y2);
}

// Rotates the whole image 270 degrees to the right
void rotate_270all(image *img)
{
	rotate_90all(img);
	rotate_90all(img);
	rotate_90all(img);
}

// Rotates the image selection 270 degrees to the right
void rotate_270select(image *img, selection *sel)
{
	rotate_90select(img, sel);
	swap(&sel->x1, &sel->y1);
	swap(&sel->x2, &sel->y2);
	rotate_90select(img, sel);
	swap(&sel->x1, &sel->y1);
	swap(&sel->x2, &sel->y2);
	rotate_90select(img, sel);
	swap(&sel->x1, &sel->y1);
	swap(&sel->x2, &sel->y2);
}

// Rotates the selection of pixels in the image
// The angle is also transformed to a positive value for simplicity
// The selection values are also swapped for the current height and width
// For a proper functioning of the program
void rotate(image *img, selection *sel, char *command)
{
	if (check_img(img) == 0) {
		return;
	}
	int angle;

	if (issquare(sel->x1, sel->y1, sel->x2, sel->y2) == 0) {
		if (!original_coords(sel->x1, sel->y1, sel->x2, sel->y2, img)) {
			printf("The selection must be a square\n");
			return;
		}
	}
	if (sscanf(command, "ROTATE %d", &angle) != 1) {
		printf("Error in the command (possible missing angle)\n");
		return;
	}
	if (check_angle(angle) == 0) {
		return;
	}
	int anglecpy = angle;
	if (angle < 0) {
		angle = 360 + angle;
	}
	int org = original_coords(sel->x1, sel->y1, sel->x2, sel->y2, img);
	switch (angle) {
			case 0: {
			}
			case 360: {
				break;
			}
			case 90: {
				if (org) {
					rotate_90all(img);
					sel->y2 = img->height;
					sel->x2 = img->width;
				} else {
					rotate_90select(img, sel);
					swap(&sel->x2, &sel->y2);
					swap(&sel->x1, &sel->y1);
				}
				break;
			}
			case 180: {
				if (org) {
					rotate_180all(img);
					sel->y2 = img->height;
					sel->x2 = img->width;
				} else {
					rotate_180select(img, sel);
				}
				break;
			}
			case 270: {
				if (org) {
					rotate_270all(img);
					sel->y2 = img->height;
					sel->x2 = img->width;
				} else {
					rotate_270select(img, sel);
				}
				break;
			}
		}
	printf("Rotated %d\n", anglecpy);
}

// Crops the image using the selection of pixels given
image *crop(image *img, selection *sel)
{
	image *new_img = malloc(sizeof(image));

	new_img->width = sel->x2 - sel->x1;
	new_img->height = sel->y2 - sel->y1;
	new_img->thresh = img->thresh;
	strcpy(new_img->format, img->format);
	if (img->format[1] != '3' && img->format[1] != '6') {
		new_img->matrix1 = allocate_single(new_img->width, new_img->height);
		for (int i = 0; i < new_img->height; i++) {
			for (int j = 0; j < new_img->width; j++) {
				new_img->matrix1[i][j] = img->matrix1[sel->y1 + i][sel->x1 + j];
			}
		}
		new_img->matrix3 = NULL;
	} else {
		new_img->matrix3 = allocate_triple(new_img->width, new_img->height);
		for (int i = 0; i < new_img->height; i++) {
			for (int j = 0; j < new_img->width; j++) {
				new_img->matrix3[i][j] = img->matrix3[sel->y1 + i][sel->x1 + j];
			}
		}
		new_img->matrix1 = NULL;
	}
	deallocate(img);
	// Reset selection to new img
	sel->x1 = 0;
	sel->y1 = 0;
	sel->x2 = new_img->width;
	sel->y2 = new_img->height;
	printf("Image cropped\n");
	return new_img;
}

// Selects a set of coordinates from the image
void selected(selection *sel, image *img, char *command)
{
	if (check_img(img) == 0) {
		return;
	}
	int x1, y1, x2, y2;
	if (sscanf(command, "SELECT %d %d %d %d", &x1, &y1, &x2, &y2) != 4) {
		printf("Invalid command\n");
		return;
	}
	if (x2 < x1) {
		swap(&x1, &x2);
	}
	if (y2 < y1) {
		swap(&y1, &y2);
	}
	if (!check_cords(x1, y1, x2, y2, img->width, img->height)) {
		return;
	}
	sel->x1 = x1;
	sel->y1 = y1;
	sel->x2 = x2;
	sel->y2 = y2;
}

// Selects the whole image
void fullhouse(selection *sel, image *img)
{
	sel->x1 = 0;
	sel->y1 = 0;
	sel->x2 = img->width;
	sel->y2 = img->height;
}

// Selects the whole image, displays error if no image is loaded
void select_all(selection *sel, image *img)
{
	sel->x1 = 0;
	sel->y1 = 0;
	sel->x2 = img->width;
	sel->y2 = img->height;
	printf("Selected ALL\n");
}

// Frees the coordinate selection
void free_sel(selection *sel)
{
	if (!sel) {
		return;
	}
	free(sel);
}

// Prints the histogram of the image
void histogram(char *command, image *img)
{
	if (check_img(img) == 0) {
		return;
	}
	int x, y, z;
	char aux_buffer[256] = {0}, count;

	// The buffer is used as a way to skip over the first part of the command,
	// "HISTOGRAM", while not overwriting the current parts of the whole
	// command. I found this a simpler way to figure out how many parameters
	// are read.
	count = sscanf(command, "%255s %d %d %d", aux_buffer, &x, &y, &z);
	if (count != 3) {
		printf("Invalid command\n");
		return;
	}
	if (img->format[1] == '3' || img->format[1] == '6') {
		printf("Black and white image needed\n");
		return;
	}
	int hist[256] = {0};
	int bin_size = 256 / y, max;

	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			unsigned char aux = img->matrix1[i][j] / bin_size;
			hist[aux]++;
		}
	}
	max = 1;
	for (int i = 0; i < y; i++) {
		if (hist[i] > max) {
			max = hist[i];
		}
	}
	for (int i = 0; i < y; i++) {
		int stars = hist[i] * x / max;
		printf("%d\t|\t", stars);
		for (int j = 0; j < stars; j++) {
			printf("*");
		}
		printf("\n");
	}
}

// Equalizes the image
void equalize(image *img)
{
	if (check_img(img) == 0) {
		return;
	}
	if (img->format[1] == '3' || img->format[1] == '6') {
		printf("Black and white image needed\n");
		return;
	}
	int area = img->height * img->width;
	// Number of appearances and the sum of previous appearances
	int hist[256] = {0}, sum[256] = {0};
	int i, j;

	for (i = 0; i < img->height; i++) {
		for (j = 0; j < img->width; j++) {
			hist[img->matrix1[i][j]]++;
		}
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j <= i; j++) {
			sum[i] += hist[j];
		}
	}
	float newpixel;

	for (i = 0; i < img->height; i++) {
		for (j = 0; j < img->width; j++) {
			newpixel = (float)(sum[img->matrix1[i][j]] * 255.0 / area);
			newpixel = clamp2(newpixel, 0, 255);
			// Newpixel is rounded by being returned as an int by
			// the clamp2 function
			img->matrix1[i][j] = newpixel;
		}
	}
	printf("Equalize done\n");
}
