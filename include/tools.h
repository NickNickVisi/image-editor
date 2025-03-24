#ifndef __tools_functions__
    #define __tools_functions__
#endif
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "image.h"

void rotate_90select(image *img, selection *sel);

void rotate_90all(image *img);

void rotate_180all(image *img);

void rotate_180select(image *img, selection *sel);

void rotate_270all(image *img);

void rotate_270select(image *img, selection *sel);

void rotate(image *img, selection *sel, char *command);

image *crop(image *img, selection *sel);

void histogram(char *command, image *img);

void equalize(image *img);

void selected(selection *sel, image *img, char *command);

void fullhouse(selection *sel, image *img);

void select_all(selection *sel, image *img);

void free_sel(selection *sel);

void deallocate(image *img);