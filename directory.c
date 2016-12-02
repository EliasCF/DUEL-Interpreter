#include <stdio.h>
#include <unistd.h>

#define LENGTH(array) (sizeof(array) / sizeof((array)[0])) //Returns the length of an array

char *replace(char array[], char find, char replace_with);
char *get_current_directory(const char *file);

//Takes a char array/string and replaces a specified char in it with another char
char *replace(char array[], char find, char replace_with) {
	int i = 0;
	while(array[i] != '\0') {
		if(array[i] == find)
			putchar(replace_with); //Replace char in index with the replace_with char
		else
			putchar(array[i]); //Keepe current char

		i++;
	}

	return array;
}

//Returns the current working directory
char *get_current_directory(const char *file) {
	char dir_buffer[2048];
	char *current_directory = getcwd(dir_buffer, LENGTH(dir_buffer));

	if(current_directory != NULL) {
		char string[4100];

		printf("Interpreting from:\n");
		sprintf(string, "%s/%s/%s", current_directory, "source", file);

		char *new_string = replace(string, '\\', '/');
		printf("\n");
		return new_string;
	}
	else perror("Current directory doesn't exist");
}