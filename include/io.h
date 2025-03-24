#ifndef __inpout_functions__
    #define __inpout_functions__
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"

image *load(char *filename);

void save(image *img, char *command);

unsigned char **allocate_single(int width, int height);

channels_3 **allocate_triple(int width, int height);

int check_img(image *img);

void dealloc_matrix3(channels_3 **matrix, int height);

void dealloc_matrix1(unsigned char **matrix, int height);