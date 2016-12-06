# DUEL-Interpreter
This is a very simple interpreter.
It interprets a very simple language that I call DUEL(Dumb Useless Esoteric Language).

Right now it only has the ability to print text to the console, ignore comments, and create one single char variable.

A simple hello world program with a comment, could looks like this:

-----------------------------------------------------------------------------------------

 !"Hello World!" ?Comment?;

-----------------------------------------------------------------------------------------




As of right now, the interpreter is only able to create and use one variable at a time.
Creating one variable and then another will simply override the first one.
The name of a variable can only be one character in length and the same goes for the value it contains(This will hopefully be changed soon).

Declaring a variable with the name a, containing the value of 1, and then printing it to the console - would look like this:

-----------------------------------------------------------------------------------------

 !
 	#a 1,
 	"#a"
 ;
 
-----------------------------------------------------------------------------------------