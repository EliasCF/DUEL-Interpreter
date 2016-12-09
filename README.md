# DUEL-Interpreter
This is a very simple interpreter.
It interprets a very simple language that I call DUEL(Dumb Useless Esoteric Language).

.

There are serveral tokens with different functions in the language:

Initiation statement: !
This token must to be the first character in the code, it tells the program that the code has been started.
If it is not found, then the interpreter will throw and error.

End statement: ;
This token must be the last character in the code, it tells the interpreter that the code is done.
If it is not the last character in the code, the interpreter will throw an error.
Also if an end statment is found anywhere in the code, even inside a mode, the interpreter will throw an error.

Talk mode: "
This token tells the interpreter to print out all the characters it meets, until it finds another Talk mode token.

Comment mod: ?
This token tells the interpreter to ignore all the characters it meets, until it meets a nextline escape sequence "\n",
or another comment mode token.

Variable init: #
This token tell the interpreter to make a variable with the name of the next character, and then after that, take the following character after the name as it's value. The interpreter then will look for a variable end token, if it's not found
the interpreter throws an error.

.

Variable end: ,
This token tells the interpreter that a varaible has been declared and initialized and end the mode.

Right now it only has the ability to print text to the console, ignore comments, and create one single char variable.

A simple hello world program with a comment, could looks like this:

-----------------------------------------------------------------------------------------

 !"Hello World!" ?Comment?;

-----------------------------------------------------------------------------------------

.

As of right now, the interpreter is only able to create and use one variable at a time.
Creating one variable and then another will simply override the first one.
The name of a variable can only be one character in length and the same goes for the value it contains

Declaring a variable with the name a, containing the value of 1, and then printing it to the console - would look like this:

-----------------------------------------------------------------------------------------

 !
 	#a 1,
 	"#a"
 ;

-----------------------------------------------------------------------------------------