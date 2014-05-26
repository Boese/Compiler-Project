/************************************************************************
* Class: Tokenizer
*
* Constructors:
*	Tokenizer()
*		calls setKeywords(), and then Tokenize()
*
* Mutators:
*		void setKeywords()
*			will add all keywords to vector m_keywords
*
*		void Tokenize()
*			This will read in input file, pass buffer of each
*			line to StateMachine::testString() and build a 
*			vector<vector<Token>> temp. Once filled it will
*			Display a list of all Token/Types
*
* Methods:
*	none
*		
*************************************************************************/

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include "Token.h"
#include <vector>

using namespace std;

class Tokenizer
{
public:
	//	set keywords()
	//	call Tokenize()
	Tokenizer();
	vector<string> m_keywords;	//keywords for Tokenizer
	vector<string> m_colors;	//Define all the colors

private:
	void setKeywords();		//set m_keywords from "keywords.txt"
	void setColors();		//set m_colors from "colors.txt"
	void Tokenize();		//Tokenize input file "myFile.txt"
	
};

#endif