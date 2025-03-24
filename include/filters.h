#ifndef __filters_functions__
    #define __filters_functions__
#endif
#include <stdio.h>
#include <string.h>
#include "image.h"
#include "io.h"

char apply_type(char *parameter);

void edge(image *img, selection *sel);

void sharpen(image *img, selection *sel);

void box_blur(image *img, selection *sel);

void gaussian_blur(image *img, selection *sel);

void apply(image *img, char *command, selection *sel);
