Compiler-Project
================
For this option, you need to write a lexical analyzer and parser for a language called Logo320.  Logo320 is a subset of Logo language that controls “turtles” on the screen.  You can write programs to create graphics using these turtles. 

Starting Logo320 Grammar:  

1. Program -> Statement  Statlist  
2. Statlist -> Statement Statlist  
3. Statlist -> lambda  
4. Statement -> 	Penup |  
  * Pendown |  
  * Forward number |  
  * Back number |  
  * Right number |  
  * Left number |  
  * Create number |  
  * If (Color == colorCode ) [ Statlist ] [ Statlist]|  
  * Setcolor colorCode |  
  * Repeat number [ Statlist ]|  
  * Define ID Statlist End |  
  * Call ID  

number is just an integer  
colorCode is a list of possible colors.  You can make your own list.  Some example colors include red, blue, black, green, yellow, purple, pink. 
ID is any combination of letters and digits but it must start with a letter. 
Bold are keywords. 

Here is an example program:
```
Create 10       //this creates 10 turtles at random locations on the  
                //screen.  Each turtle is also given a random color  
				        //Each turtle is also facing a random direction  
Penup           // do not draw with turtle movement  
Forward 10      // move all turtles on the screen 10 pixels in the  
                // direction that they are headed  
Pendown         // do draw with next turtle movement  
Right 90        // turn all turtles on screen 90 degrees  
Repeat 4 [Forward 10 Right 90 ]  
                // repeat Forward 10 and Right 90 4 times for all  
                // turtles on the screen.  Since pen is down,  
                //  these turtles will leave a trail  

If (Color == pink ) [ Setcolor red ] [ Setcolor blue]  
                //turn all pink turtles red and all other turtles blue  
Define drawbox Repeat 4 [Forward 10 Right 90] End  
                //define a drawbox function with a repeat command in it  
Call drawbox    //call the drawbox function  
```

Project Requirements:  
1. Implement a lexical analyzer to tokenize the Logo320 program.  
2. Implement a parser to check the syntax of the language (you can use either recursive descent or LL(1))  
3. Construct a parse tree to save all the commands recognized in the parser.  
4. Implement some semantic analysis – checks to see if a function has been declared before use.  
5. Create a simple GUI program to simulate the program, i.e. draw something in the window as specified by the program.      You don’t have to show actual turtles, just their trails.  
