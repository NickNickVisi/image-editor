#ifndef __filters_functions__
    #define __filters_functions__

#include <stdio.h>
#include "image.h"
#include "io.h"

int apply_type(char *parameter);

void edge(image *img, selection *sel);

void sharpen(image *img, selection *sel);

void box_blur(image *img, selection *sel);

void gaussian_blur(image *img, selection *sel);

void apply(image *img, char *command, selection *sel);

#endif
