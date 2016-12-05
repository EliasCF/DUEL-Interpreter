//
//Dumb Useless Esoretic Language - Interpreter
//
//To compile this interpeter in the command line with MinGW, write: g++ main.c -o main.exe

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "error.c"
#include "directory.c"

struct Token {
	char initiation_statement; //This token is found as the fist char, it signals the start of a program
	char end_statement;        //This token is found as the last char, it signals the end of a program
	char talk_mode;			   //This token tells the interpeter that the next stream of chars should be printed to the console
	char comment_mode;		   //This token tells the interpreter to ignore the next stream of chars.
	char variable_init;        //This token tells the interperter that a variable is being declared, and it should look for a variable name
	char variable_end;         //This token tells the interpeter that the variable has been declared
};

int main(void)
{
	struct Token token = {'!', ';', '"', '?', '#', ','}; //Declare token values

	const char *source_path = get_current_directory("code.duel"); //File path

	bool talk_mode = false;	//Talk mode variable
	bool talk_mode_variable = false; //If a variable_init token is found within the talk mode

	bool initiation_statement_found = false; //Initiation statement related variable

	bool strict_mode = true; //strict mode boolean

	//Comment mode variables
	bool comment_mode = false;
	int comment_count = 0;

	bool variable_mode = false;
	char variable_name[1]; //Right now the variable name can only be one char long, this should be fixed later
	char variable_value;
	bool variable_mode_value = false;

	int count_line = 1; //Counting the amounts of lines in the code
	int count_char = 0; //Counting the amount of chars in the code


	char file_buffer[1000];
	FILE *file = fopen(source_path, "r");

	file_exists(file); //Make sure the file exsists
	check_for_initation_statement(source_path); //Make sure the first char in the file is an initiation statement
	check_for_end_statement(source_path); //Make sure the last char in the file is an end statement

	//If check_for_initation_statement didn't throw an error,
	//then we know there is an initiation statement
	printf("--- The program has successfully been initatied\n\n");

	//Read the file char by char
	char ch;
	while((ch = fgetc(file)) != EOF)
	{
		count_char++;
		if(ch == '\n') {
			count_line++;
			count_char = 0;
		}

		//If the current char is the initiation statement we jump to the next char in the file
		if(!initiation_statement_found) {
			initiation_statement_found = true;
			continue;
		}

		//If variable mode value is on, then we store the current char in the variable value char
		if(variable_mode_value) {
			variable_value = ch;
			printf("The varaible '%c' equals '%c'\n\n", variable_name[0], variable_value);
			variable_mode_value = false;
			continue;
		}

		//If variable mode is on
		if(variable_mode) {
			if(ch == ' ') {
				variable_mode = false;
				variable_mode_value = true;
				continue;
			}

			if(ch == token.variable_end) {
				variable_mode = false;
				continue;
			}

			sprintf(variable_name, "%c", ch); //Concat the variable name together char by char
			printf("Variable '%c' has been declared\n", variable_name[0]);
		}

		//If talk mode is on
		if(talk_mode) {
			//If an end statement is found in talk mode
			if(ch == token.end_statement) {
				//Either the talkmode is unclosed or there is an end statement in the talk mode
				char buffer[1000];
				sprintf(buffer, "Error: \nThe interpreter detected an unclosed talk mode at %d:%d", count_line, count_char);
				throw_error(buffer);
			}

			//If a newline string literal is found, then end talk mode
			if(ch == '\n') {
				char buffer[1000];
				sprintf(buffer, "Error: \nThe interpreter detected an unclosed talk mode at %d:%d", count_line, count_char);
				throw_error(buffer);
			}

			//If a talk mode token is found, then end talk mode
			if(ch == token.talk_mode) {
				talk_mode = false;
				printf("\n");
				continue;
			}

			//If a variable_init token is found within the talk mode, talk mode variable is on
			if(ch == token.variable_init) {
				talk_mode_variable = true;
				continue;
			}

			if(talk_mode_variable) {
				if(ch == variable_name[0]) {
					printf("%c", variable_value);
					talk_mode_variable = false;
					continue;
				}

				char buffer[1000];
				sprintf(buffer, "There is no variable with the name '%c'", ch);
				throw_error(buffer);
			}

			//If none of the above statements werer true, then print out the current char
			printf("%c", ch);
		}

		//If comment mode is on
		if(comment_mode) {
			//If an end statement is found in comment mode
			if(ch == token.end_statement) {
				//Either the comment mode is unclosed or there is an end statement in the comment mode
				char buffer[1000];
				sprintf(buffer, "Error: \nThe interpreter detected an unclosed comment mode at %d:%d", count_line, count_char);
				throw_error(buffer);
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
		if(!talk_mode && !comment_mode && !variable_mode && !variable_mode_value) {
			//If strict mode is on an the current char is not a token or string literal, then we throw an error
			if(strict_mode) {
				if (ch != '\n' && ch != '\r' && ch != ' ' && ch != '\t' &&
					ch != token.initiation_statement && ch != token.end_statement &&
					ch != token.talk_mode && ch != token.comment_mode &&
					ch != token.variable_init && ch != token.variable_end) {
						char buffer[1000];
						sprintf(buffer, "%s'%c' at %d:%d", "An unidetified character was found with the value of: ", ch, count_line, count_char);
						throw_error(buffer);
				}
			}

			//If we find an initiation statement we throw an error
			if(initiation_statement_found && ch == token.initiation_statement) {
				char buffer[1000];
				sprintf(buffer, "Error: \nThe program has already been initiated with the an initiation statment at %d:%d", count_line, count_char);
				throw_error(buffer);
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

				fclose(file);
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

			//If a variable initiation token is found we begin variable mode
			if(ch == token.variable_init) {
				variable_mode = true;
			}
		}
	}

	fclose(file); //Close file

	return 0;
}