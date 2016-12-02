//
//Dumb Useless Esoretic Language - Interpreter
//
//To compile this interpeter in the command line with MinGW, write: g++ main.c -o main.exe

//TODO:
//Detect which line and character the an error comes from

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "error.c"
#include "directory.c"

struct Token {
	char initiation_statement;
	char end_statement;
	char talk_mode;
	char comment_mode;
};

int main(void)
{
	struct Token token = {'!', ';', '"', '?'}; //Declare token values

	const char *source_path = get_current_directory("code.duel");

	//Talk mode variable
	bool talk_mode = false;

	//Initiation statement related variable
	bool initiation_statement_found = false;

	//strict mode boolean
	bool strict_mode = true;

	//Comment mode variables
	bool comment_mode = false;
	int comment_count = 0;


	char file_buffer[1000]; //Buffer for opening the file
	FILE *file = fopen(source_path, "r");

	file_exists(file); //Make sure the file exsists, if not, then throw an error
	check_for_initation_statement(source_path); //Make sure the first char in the file is an initiation statement
	check_for_end_statement(source_path); //Make sure the last char in the file is an end statement

	//If check_for_initation_statement didn't throw an error,
	//then we know there is an initiation statement
	printf("--- The program has successfully been initatied\n\n");

	char ch;
	while((ch = fgetc(file)) != EOF)
	{
		//If the current char is the initiation statement we jump to the next char in the file
		if(!initiation_statement_found) {
			initiation_statement_found = true;
			continue;
		}

		//If talkmode is on
		if(talk_mode)
		{
			//If an end statement is found in talk mode
			if(ch == token.end_statement) {
				//Either the talkmode is unclosed or there is an end statement in the talk mode
				throw_error("Error: \nThe interpreter detected an unclosed talk mode");
			}

			//If a newline string literal is found, then end talk mode
			if(ch == '\n') {
				throw_error("Error: \nThe interpreter detected an unclosed talk mode");
			}

			//If a talk mode token is found, then end talk mode
			if(ch == token.talk_mode) {
				talk_mode = false;
				printf("\n");
				continue;
			}

			//If none of the above statements werer true, then print out the current char
			printf("%c", ch);
		}

		//If comment mode is on
		if(comment_mode)
		{
			//If an end statement is found in comment mode
			if(ch == token.end_statement) {
				//Either the comment mode is unclosed or there is an end statement in the comment mode
				throw_error("Error: \nThe interpreter detected an unclosed comment mode");
			}

			//If a newline string literal is found, then end comment mode
			if(ch == '\n') {
				comment_mode = false;
				comment_count++;
				continue;
			}

			//If a comment mode token is found, then end comment mode
			if(ch == token.comment_mode) {
				comment_mode = false;
				comment_count++;
				continue;
			}
		}

		//If the interpreter is not in talk_mode or in comment_mode,
		//then look for tokens
		if(!talk_mode && !comment_mode)
		{
			if(strict_mode) {
				if(ch != '\n' && ch != '\r' && ch != ' ' && ch != '\t' &&
					ch != token.initiation_statement && ch != token.end_statement &&
					ch != token.talk_mode && ch != token.comment_mode) {
						char buffer[1000];
						sprintf(buffer, "%s%c", "An unidetified character was found with the value: ", ch);
						throw_error(buffer);
				}
			}

			//If we find an initiation statement we throw an error
			if(initiation_statement_found && ch == token.initiation_statement) {
				throw_error("Error: \nThe program has already been initiated with the an initiation statment '!'");
			}

			//If we find an end statemnt we print out information and end the program
			if(ch == token.end_statement) {
				if(comment_count > 0) {
					printf("\n--- End report: The interpreter encounted %d comment(s)\n", comment_count);
					printf("--- The code was interpreted successfully");
				}
				else {
					printf("\n--- The code was interpreted successfully");
				}

				getchar();
				exit(0);
			}

			//If a talk mode token is found we begin talk mode
			if(ch == token.talk_mode) {
				talk_mode = true;
			}

			//If a comment mode token is found we begin comment mode
			if(ch == token.comment_mode) {
				comment_mode = true;
			}
		}
	}

	fclose(file);

	return 0;
}