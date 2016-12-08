#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void throw_error(const char *message);
void check_for_end_statement(const char *path);
void check_for_initation_statement(const char *path);
void file_exists(FILE *file);

//print out an error, and then exit the program
void throw_error(const char *message)
{
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED); //Set foreground color as red

	printf("%s\n", message);
	printf("\nPress any key to continue...");

	getchar();
	exit(0);
}

//Make sure there is an end statement at the end of the code
//If not then throw an error
void check_for_end_statement(const char *path)
{
	char *contents;

	char file_buffer[1000];
	FILE *file = fopen(path, "r");

	while(fgets(file_buffer, 1000, file) != NULL) {
		contents = file_buffer;
	}

	if(contents[strlen(contents) - 1] != ';') {
		throw_error("Error: \nThe interpreter could not find an end statement \";\"");
	}
}

//Make sure the first char in the code is an initation statement
//If not, then throw an error
void check_for_initation_statement(const char *path)
{
	char file_buffer[1000];
	FILE *file = fopen(path, "r");

	char ch;
	while((ch = fgetc(file)) != EOF) {
		if(ch != '!') {
			throw_error("Error: \nThe interpreter could not find an initation statement: \"!\"");
		} else {
			break;
		}
	}


}

//Make sure file exists
//If not, then throw an error
void file_exists(FILE *file)
{
	if(!file) {
		perror("error");
	}
}