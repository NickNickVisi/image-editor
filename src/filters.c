#include "../include/filters.h"

// Chooses what type of filter should be applied
char apply_type(char *parameter)
{
	if (strcmp(parameter, "EDGE") == 0) {
		return 'a';
	}
	if (strcmp(parameter, "SHARPEN") == 0) {
		return 'b';
	}
	if (strcmp(parameter, "BLUR") == 0) {
		return 'c';
	}
	if (strcmp(parameter, "GAUSSIAN_BLUR") == 0) {
		return 'd';
	}
	return 'e';
}

// Sets the value to min or max if it is outside the interval
int clamp(int x, int min, int max)
{
	if (x < min) {
		return min;
	}
	if (x > max) {
		return max;
	}
	return x;
}

// Applies the edge filter to the loaded image selection
void edge(image *img, selection *sel)
{
	int kernel[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
	channels_3 **new_matrix = allocate_triple(img->width, img->height);
	int i, j, k, l, sumr, sumg, sumb;
	int width = img->width, height = img->height;

	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
				new_matrix[i][j] = img->matrix3[i][j];
			} else {
				sumr = 0;
				sumg = 0;
				sumb = 0;
				for (k = 0; k < 3; k++) {
					for (l = 0; l < 3; l++) {
						sumr += img->matrix3[i + k - 1][j + l - 1].r
						* kernel[k][l];
						sumg += img->matrix3[i + k - 1][j + l - 1].g
						* kernel[k][l];
						sumb += img->matrix3[i + k - 1][j + l - 1].b
						* kernel[k][l];
					}
				}
				new_matrix[i][j].r = clamp(sumr, 0, 255);
				new_matrix[i][j].g = clamp(sumg, 0, 255);
				new_matrix[i][j].b = clamp(sumb, 0, 255);
			}
		}
	}
	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			img->matrix3[i][j] = new_matrix[i][j];
		}
	}
	dealloc_matrix3(new_matrix, img->height);
}

// Applies the sharpen filter to the loaded image selection
void sharpen(image *img, selection *sel)
{
	int kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
	channels_3 **new_matrix = allocate_triple(img->width, img->height);
	int i, j, k, l, sumr, sumg, sumb;
	int width = img->width, height = img->height;

	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
				new_matrix[i][j] = img->matrix3[i][j];
			} else {
				sumr = 0;
				sumg = 0;
				sumb = 0;
				for (k = 0; k < 3; k++) {
					for (l = 0; l < 3; l++) {
						sumr += img->matrix3[i + k - 1][j + l - 1].r
						* kernel[k][l];
						sumg += img->matrix3[i + k - 1][j + l - 1].g
						* kernel[k][l];
						sumb += img->matrix3[i + k - 1][j + l - 1].b
						* kernel[k][l];
					}
				}
				new_matrix[i][j].r = clamp(sumr, 0, 255);
				new_matrix[i][j].g = clamp(sumg, 0, 255);
				new_matrix[i][j].b = clamp(sumb, 0, 255);
			}
		}
	}
	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			img->matrix3[i][j] = new_matrix[i][j];
		}
	}
	dealloc_matrix3(new_matrix, img->height);
}

// Applies the box blur filter to the loaded image selection
void box_blur(image *img, selection *sel)
{
	int kernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
	channels_3 **new_matrix = allocate_triple(img->width, img->height);
	int i, j, k, l, sumr, sumg, sumb;
	int width = img->width, height = img->height;

	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
				new_matrix[i][j] = img->matrix3[i][j];
			} else {
				sumr = 0;
				sumg = 0;
				sumb = 0;
				for (k = 0; k < 3; k++) {
					for (l = 0; l < 3; l++) {
						sumr += img->matrix3[i + k - 1][j + l - 1].r
						* kernel[k][l];
						sumg += img->matrix3[i + k - 1][j + l - 1].g
						* kernel[k][l];
						sumb += img->matrix3[i + k - 1][j + l - 1].b
						* kernel[k][l];
					}
				}
				new_matrix[i][j].r = clamp(sumr / 9, 0, 255);
				new_matrix[i][j].g = clamp(sumg / 9, 0, 255);
				new_matrix[i][j].b = clamp(sumb / 9, 0, 255);
			}
		}
	}
	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			img->matrix3[i][j] = new_matrix[i][j];
		}
	}
	dealloc_matrix3(new_matrix, img->height);
}

// Applies the gaussian blur filter to the loaded image selection
void gaussian_blur(image *img, selection *sel)
{
	int kernel[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
	channels_3 **new_matrix = allocate_triple(img->width, img->height);
	int i, j, k, l, sumr, sumg, sumb;
	int width = img->width, height = img->height;

	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			if (i == 0 || j == 0 || i == height - 1 || j == width - 1) {
				new_matrix[i][j] = img->matrix3[i][j];
			} else {
				sumr = 0;
				sumg = 0;
				sumb = 0;
				for (k = 0; k < 3; k++) {
					for (l = 0; l < 3; l++) {
						sumr += img->matrix3[i + k - 1][j + l - 1].r *
						kernel[k][l];
						sumg += img->matrix3[i + k - 1][j + l - 1].g *
						kernel[k][l];
						sumb += img->matrix3[i + k - 1][j + l - 1].b *
						kernel[k][l];
					}
				}
				new_matrix[i][j].r = clamp(sumr / 16, 0, 255);
				new_matrix[i][j].g = clamp(sumg / 16, 0, 255);
				new_matrix[i][j].b = clamp(sumb / 16, 0, 255);
			}
		}
	}
	for (i = sel->y1; i < sel->y2; i++) {
		for (j = sel->x1; j < sel->x2; j++) {
			img->matrix3[i][j] = new_matrix[i][j];
		}
	}
	dealloc_matrix3(new_matrix, img->height);
}

// Applies the aforementioned filters to the image
void apply(image *img, char *command, selection *sel)
{
	if (check_img(img) == 0) {
		return;
	}
	char parameter[30];

	if (sscanf(command, "APPLY %s", parameter) != 1) {
		printf("Invalid command\n");
		return;
	}
	if (img->format[1] != '3' && img->format[1] != '6') {
		printf("Can only apply image filters to coloured images.\n");
		return;
	}
	char type = apply_type(parameter);

	switch (type) {
		case 'a': {
			edge(img, sel);
			break;
		}
		case 'b': {
			sharpen(img, sel);
			break;
		}
		case 'c': {
			box_blur(img, sel);
			break;
		}
		case 'd': {
			gaussian_blur(img, sel);
			break;
		}
		case 'e': {
			printf("APPLY parameter invalid\n");
			return;
		}
	}
	printf("APPLY %s done\n", parameter);
}
