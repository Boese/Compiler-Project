Compiler-Project
================
For this option, you need to write a lexical analyzer and parser for a language called Logo320.  
Logo320 is a subset of Logo language that controls “turtles” on the screen.  
You can write programs to create graphics using these turtles. 
___
Logo320 Grammar:
===
```
Program   -> Statement  Statlist  
Statlist  -> Statement Statlist  
Statlist  -> lambda  
Statement -> Penup
          | Pendown
          | Forward Number
          | Back Number
          | Right Number
          | Left Number
          | Create Number
          | If (Color == colorcode ) [ Statlist ] [ Statlist]
          | Setcolor colorcode
          | Repeat Number [ Statlist ]
          | Define Id Statlist End
          | Call Id
```

 *  Number is just an integer.  
 *  colorcode is a list of possible colors.   
 *  Id is any combination of letters and digits but it must start with a letter.  

#### Valid colors in colorcode:
```
blue
green
black
pink
yellow
orange
red
white
purple
```
___
Completed LL(1) Parse Table:
===

|	   | Program            | Statlist           | Statement                                           |
|:----------:|:------------------:|:------------------:|:----------------------------------------------------|
|**Penup**   | Statement Statlist | Statement Statlist | Penup                                               |
|**Pendown** | Statement Statlist | Statement Statlist | Pendown                                             |
|**Forward** | Statement Statlist | Statement Statlist | Forward number                                      |
|**Back**	   | Statement Statlist | Statement Statlist | Back number                                         |
|**Right**   | Statement Statlist | Statement Statlist | Right number                                        |
|**Left**	   | Statement Statlist | Statement Statlist | Left number                                         |
|**Create**  | Statement Statlist | Statement Statlist | Create number                                       |
|**If**	   | Statement Statlist | Statement Statlist | If ( color == colorcode ) [ Statlist ] [ Statlist ] |
|**SetColor**| Statement Statlist | Statement Statlist | SetColor colorcode                                  |
|**Repeat**  | Statement Statlist | Statement Statlist | Repeat number [ Statlist ]                          |
|**Define**  | Statement Statlist | Statement Statlist | Define id Statlist End                              |
|**Call**	   | Statement Statlist | Statement Statlist | Call id                                             |
|**]**	   |	              | lambda	     |                                                     |
|**End**	   |	              | lambda	     |                                                     |
|**$**	   |	              | lambda	     |                                                     |
 
___
Parser Table Input File:
===
 
```
Program Penup Statement;Statlist
Program Pendown Statement;Statlist
Program Forward Statement;Statlist
Program Back Statement;Statlist
Program Right Statement;Statlist
Program Left Statement;Statlist
Program Create Statement;Statlist
Program If Statement;Statlist
Program SetColor Statement;Statlist
Program Repeat Statement;Statlist
Program Define Statement;Statlist
Program Call Statement;Statlist
Statlist Penup Statement;Statlist
Statlist Pendown Statement;Statlist
Statlist Forward Statement;Statlist
Statlist Back Statement;Statlist
Statlist Right Statement;Statlist
Statlist Left Statement;Statlist
Statlist Create Statement;Statlist
Statlist If Statement;Statlist
Statlist SetColor Statement;Statlist
Statlist Repeat Statement;Statlist
Statlist Define Statement;Statlist
Statlist Call Statement;Statlist
Statlist ] lambda
Statlist End lambda
Statlist $ lambda
Statement Penup Penup
Statement Pendown Pendown
Statement Forward Forward;Number
Statement Back Back;Number
Statement Right Right;Number
Statement Left Left;Number
Statement Create Create;Number
Statement If If;(;Color;==;colorcode;);[;Statlist;];[;Statlist;]
Statement SetColor SetColor;colorcode
Statement Repeat Repeat;Number;[;Statlist;]
Statement Define Define;Id;Statlist;End
Statement Call Call;Id
```
___
Here is an example program:
===
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
___
Tokenized Example Format:
===
```
Create     Create
10         Number
Penup      Penup
Forward    Forward
10         Number
Pendown    Pendown
Right      Right
90         Number
Repeat     Repeat
4          Number
[          [
Forward    Forward
10         Number
Right      Right
90         Number
]          ]
If         If
(          (
Color      Color
==         ==
pink       colorcode
)          )
[          [
SetColor   SetColor
red        colorcode
]          ]
[          [
SetColor   SetColor
blue       colorcode
]          ]
Define     Define
drawbox    Id
Repeat     Repeat
4          Number
[          [
Forward    Forward
10         Number
Right      Right
90         Number
]          ]
End        End
Call       Call
drawbox    Id
```
___
Project Requirements:
===
1. Implement a lexical analyzer to tokenize the Logo320 program.  
2. Implement a parser to check the syntax of the language (you can use either recursive descent or LL(1))  
3. Construct a parse tree to save all the commands recognized in the parser.  
4. Implement some semantic analysis – checks to see if a function has been declared before use.  
5. Create a simple GUI program to simulate the program, i.e. draw something in the window as specified by the program.      You don’t have to show actual turtles, just their trails.  
