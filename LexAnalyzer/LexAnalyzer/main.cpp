/***********************************************************
* Author:				Chris Boese
* Date Created:			02/12/2014
* Last Modification Date:	02/14/2014
* Lab Number:			CST 229 Lab 1
* Filename:				main.cpp
*
* Overview:
*	This program will Tokenize a C like program located
*	in "myFile.txt". It needs 3 files to operate. It will
*	print a list of Tokens/Types to output
*
* Input:
*	The input is embedded within the classes, but 3 files
*	are needed in solution to work. These include:
*	"myFile.txt"	-	The C like program file
*	"combinedStates.txt"	-	The state Machine
*	"keywords.txt"	-	all available keywords
*
* Output:
*	Will print a list of Tokens/Types based on input file
*
*	Ex.
*	function              -  Identifier
*	printOddNumbers       -  Identifier
*	(                     -  Symbol
*	x                     -  Identifier
*	)                     -  Symbol
*
************************************************************/

#include <iostream>
#include <string>
#include "Tokenizer.h"

using namespace std;

void main()
{
	//Tokenize myFile.txt
	Tokenizer t = Tokenizer();

	system("pause");
}