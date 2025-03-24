#include "../include/image.h"
#include "../include/io.h"
#include "../include/tools.h"
#include "../include/filters.h"

// Returns the type of command that was read from input
char check_type(char *string)
{
	if (strncmp(string, "LOAD", 4) == 0) {
		return 'a';
	}
	if (strncmp(string, "SELECT ALL", 10) == 0) {
		return 'b';
	}
	if (strncmp(string, "SELECT", 6) == 0) {
		return 'c';
	}
	if (strncmp(string, "HISTOGRAM", 9) == 0) {
		return 'd';
	}
	if (strncmp(string, "EQUALIZE", 8) == 0) {
		return 'e';
	}
	if (strncmp(string, "ROTATE", 6) == 0) {
		return 'f';
	}
	if (strncmp(string, "CROP", 4) == 0) {
		return 'g';
	}
	if (strncmp(string, "APPLY", 5) == 0) {
		return 'h';
	}
	if (strncmp(string, "SAVE", 4) == 0) {
		return 'i';
	}
	if (strncmp(string, "EXIT", 4) == 0) {
		return 'j';
	}
	return 'k';
}

// Main function where the selection of commands is made
int main(void)
{
	char command[256] = {0}, filename[256] = {0};
	image *img = NULL;
	selection *sel = NULL;
	int running = 1;
	printf("Please insert command.\n");

	while (running) {
		fgets(command, 256, stdin);
		if (command[strlen(command) - 1] == '\n') {
			command[strlen(command) - 1] = '\0';
		}
		char type = check_type(command);
		switch (type) {
		case 'a': {
			deallocate(img);
			strcpy(filename, command + 5);
			img = load(filename);
			break;
		}
		case 'b': {
			if (check_img(img)) {
				if (!sel) {
					sel = malloc(sizeof(selection));
				}
				select_all(sel, img);
			}
			break;
		}
		case 'c': {
			if (!sel) {
				sel = malloc(sizeof(selection));
			}
			selected(sel, img, command);
			break;
		}
		case 'd': {
			histogram(command, img);
			break;
		}
		case 'e': {
			equalize(img);
			break;
		}
		case 'f': {
			if (!sel && img) {
				sel = malloc(sizeof(selection));
				fullhouse(sel, img);
			}
			rotate(img, sel, command);
			break;
		}
		case 'g': {
			if (check_img(img)) {
				if (!sel) {
					sel = malloc(sizeof(selection));
					fullhouse(sel, img);
				}
				img = crop(img, sel);
			}
			break;
		}
		case 'h': {
			if (!sel && img) {
				sel = malloc(sizeof(selection));
				fullhouse(sel, img);
			}
			apply(img, command, sel);
			break;
		}
		case 'i':{
			save(img, command);
			break;
		}
		case 'j': {
			free_sel(sel);
			if (img) {
				deallocate(img);
			} else {
				printf("No image loaded\n");
				running = 0;
			}
			running = 0;
			break;
		}
		case 'k': {
			printf("Invalid command\n");
			break;
		}
		}
	}
	return 0;
}
