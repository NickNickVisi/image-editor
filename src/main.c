#include "../include/image.h"
#include "../include/io.h"
#include "../include/tools.h"
#include "../include/filters.h"

// Returns the type of command that was read from input
int check_type(char *string)
{
	if (strncmp(string, "LOAD", 4) == 0)
		return 1;

	if (strncmp(string, "SELECT ALL", 10) == 0)
		return 2;

	if (strncmp(string, "SELECT", 6) == 0)
		return 3;

	if (strncmp(string, "HISTOGRAM", 9) == 0)
		return 4;

	if (strncmp(string, "EQUALIZE", 8) == 0)
		return 5;

	if (strncmp(string, "ROTATE", 6) == 0)
		return 6;

	if (strncmp(string, "CROP", 4) == 0)
		return 7;

	if (strncmp(string, "APPLY", 5) == 0) 
		return 8;

	if (strncmp(string, "SAVE", 4) == 0) 
		return 9;

	if (strncmp(string, "EXIT", 4) == 0)
		return 10;

	return 11;
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
		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';

		int type = check_type(command);

		switch (type) {
			case 1: 
				deallocate(img);
				strcpy(filename, command + 5);
				img = load(filename);
				break;

			case 2:
				if (check_img(img)) {
					if (!sel)
						sel = malloc(sizeof(selection));
					select_all(sel, img);
				}
				break;

			case 3:
				if (!sel)
					sel = malloc(sizeof(selection));
				selected(sel, img, command);
				break;

			case 4:
				histogram(command, img);
				break;

			case 5:
				equalize(img);
				break;

			case 6:
				if (!sel && img) {
					sel = malloc(sizeof(selection));
					fullhouse(sel, img);
				}
				rotate(img, sel, command);
				break;

			case 7: 
				if (check_img(img)) {
					if (!sel) {
						sel = malloc(sizeof(selection));
						fullhouse(sel, img);
					}
					img = crop(img, sel);
				}
				break;

			case 8:
				if (!sel && img) {
					sel = malloc(sizeof(selection));
					fullhouse(sel, img);
				}
				apply(img, command, sel);
				break;

			case 9:
				save(img, command);
				break;

			case 10:
				free_sel(sel);
				if (img)
					deallocate(img);
				else
					printf("No image loaded\n");
				running = 0;
				break;

			case 11:
				printf("Invalid command\n");
				break;
			}
	}
	return 0;
}
