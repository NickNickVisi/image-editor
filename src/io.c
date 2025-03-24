#include "../include/io.h"

image *load(char *filename)
{
	FILE *file = fopen(filename, "rb");

	if (!file) {
		printf("Failed to load %s\n", filename);
		return NULL;
	}
	image *img = malloc(sizeof(image));
	int x;
	img->matrix1 = NULL;
	img->matrix3 = NULL;
	fscanf(file, "%2s ", img->format);
	fscanf(file, "%d %d %d ", &img->width, &img->height, &img->thresh);
	switch (img->format[1]) {
		case '1': {

		}
		case '2': {
			img->matrix1 = allocate_single(img->width, img->height);
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fscanf(file, "%d ", &x);
					img->matrix1[i][j] = (unsigned char)x;
				}
			}
			break;
		}
		case '3': {
			img->matrix3 = allocate_triple(img->width, img->height);
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fscanf(file, "%d ", &x);
					img->matrix3[i][j].r = (unsigned char)x;
					fscanf(file, "%d ", &x);
					img->matrix3[i][j].g = (unsigned char)x;
					fscanf(file, "%d ", &x);
					img->matrix3[i][j].b = (unsigned char)x;
				}
			}
			break;
		}
		case '4': {
			
		}
		case '5': {
			img->matrix1 = allocate_single(img->width, img->height);
			for (int i = 0; i < img->height; i++) {
				fread(img->matrix1[i], sizeof(unsigned char), img->width, file);
			}
			break;
		}
		case '6': {
			img->matrix3 = allocate_triple(img->width, img->height);
			for (int i = 0; i < img->height; i++) {
				fread(img->matrix3[i], sizeof(channels_3), img->width, file);
			}
			break;
		}
	}
	fclose(file);
	printf("Loaded %s\n", filename);
	return img;
}

// Saves the image to a given file, be it human readable or binary
void save(image *img, char *command)
{
	if (check_img(img) == 0) {
		return;
	}
	FILE *output;
	char filename[256] = {0}, mode[16] = {0};
	int i, j;

	if (sscanf(command, "SAVE %s %s", filename, mode) < 1) {
		printf("Invalid SAVE command(possible missing parameter)\n");
		return;
	}
	if (strncmp(mode, "ascii", 5) == 0) {
		output = fopen(filename, "wt");
		if (img->format[1] == '3' || img->format[1] == '6') {
			img->format[1] = '3';
			fprintf(output, "%s\n", img->format);
			fprintf(output, "%d %d\n", img->width, img->height);
			fprintf(output, "%d\n", img->thresh);
			for (i = 0; i < img->height; i++) {
				for (j = 0; j < img->width; j++) {
					fprintf(output, "%d ", img->matrix3[i][j].r);
					fprintf(output, "%d ", img->matrix3[i][j].g);
					fprintf(output, "%d ", img->matrix3[i][j].b);
				}
				fprintf(output, "\n");
			}
		} else {
			img->format[1] = '2';
			fprintf(output, "%s\n", img->format);
			fprintf(output, "%d %d\n", img->width, img->height);
			fprintf(output, "%d\n", img->thresh);
			for (i = 0; i < img->height; i++) {
				for (j = 0; j < img->width; j++) {
					fprintf(output, "%d ", img->matrix1[i][j]);
				}
				fprintf(output, "\n");
			}
		}
	} else {
		output = fopen(filename, "wb");
		int width = img->width;
		if (img->format[1] == '3' || img->format[1] == '6') {
			img->format[1] = '6';
			fprintf(output, "%s\n", img->format);
			fprintf(output, "%d %d\n", img->width, img->height);
			fprintf(output, "%d\n", img->thresh);
			for (i = 0; i < img->height; i++) {
				fwrite(img->matrix3[i], sizeof(channels_3), width, output);
			}
		} else {
			img->format[1] = '5';
			fprintf(output, "%s\n", img->format);
			fprintf(output, "%d %d\n", img->width, img->height);
			fprintf(output, "%d\n", img->thresh);
			for (i = 0; i < img->height; i++) {
				fwrite(img->matrix1[i], sizeof(unsigned char), width, output);
			}
		}
	}
	fclose(output);
	printf("Saved %s\n", filename);
}

// Allocates memory for a single channel colour matrix
unsigned char **allocate_single(int width, int height)
{
	unsigned char **matrix = (unsigned char **)malloc(height * sizeof(unsigned char *));
	for (int i = 0; i < height; i++) {
		matrix[i] = malloc(width * sizeof(unsigned char));
	}
	return matrix;
}

// Allocates memory for a triple channel colour matrix
channels_3 **allocate_triple(int width, int height)
{
	channels_3 **matrix = (channels_3 **)malloc(height * sizeof(channels_3 *));
	for (int i = 0; i < height; i++) {
		matrix[i] = malloc(width * sizeof(channels_3));
	}
	return matrix;
}

// Checks whether an image is loaded or not
int check_img(image *img)
{
	if (!img) {
		printf("No image loaded\n");
		return 0;
	}
	return 1;
}

// Deallocation of the memory used by the triple channel matrix
void dealloc_matrix3(channels_3 **matrix, int height)
{
	for (int i = 0; i < height; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

// Deallocation of the memory used by the single channel matrix
void dealloc_matrix1(unsigned char **matrix, int height)
{
	for (int i = 0; i < height; i++) {
		free(matrix[i]);
	}
	free(matrix);
}
