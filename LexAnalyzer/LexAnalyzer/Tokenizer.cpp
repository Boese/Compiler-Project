#include "Tokenizer.h"
#include "StateMachine.h"
#include <string>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;

#define fileOpenFailure_

//Set all the keywords from "keywords.txt" to m_keywords vector
void Tokenizer::setKeywords()
{
	try
	{
		//use istream iterator to read in keywords
		typedef  istream_iterator<string>  InIter;
		ifstream File("keywords2.txt");

		//try to open file, throw exception if not
		if (!File)
			throw fileOpenFailure_;

		//STL copy function, copy all keywords
		copy(InIter(File),
			InIter(),
			inserter(m_keywords, m_keywords.end()));

		File.close();	//close file
	}
	catch (int e)	//catch thrown exception, output exception error
	{
		cout << "Error number : " << e << ", File not found" << endl;
	}
}

void Tokenizer::setColors()
{
	try
	{
		//use istream iterator to read in keywords
		typedef  istream_iterator<string>  InIter;
		ifstream File("colors2.txt");

		//try to open file, throw exception if not
		if (!File)
			throw fileOpenFailure_;

		//STL copy function, copy all keywords
		copy(InIter(File),
			InIter(),
			inserter(m_colors, m_colors.end()));

		File.close();	//close file
	}
	catch (int e)	//catch thrown exception, output exception error
	{
		cout << "Error number : " << e << ", File not found" << endl;
	}
}

//******Helper function: This binary_functions is used to help StateMachine::Tokenize()*****//
struct  isKeyword : public  binary_function<string, string, bool>
{
	bool  operator()(const string  &keyword, const string  &var)  const
	{
		//return true if transition start state is equal to m_currentState
		if (keyword.compare(var) == 0)
			return true;
		return false;
	}
};

struct  isColor : public  binary_function<string, string, bool>
{
	bool  operator()(const string  &keyword, const string  &var)  const
	{
		//return true if transition start state is equal to m_currentState
		if (keyword.compare(var) == 0)
			return true;
		return false;
	}
};

//*********************************************************************************//

/**************************************************************
*   Entry:  none
*
*    Exit:  Print list of Tokens/Types
*
* Purpose:  This function will open the input File and read each line
*			to a buffer. For each buffer it will pass it in to StateMachine::testString()
*			and save the vector<Token> it returns to vector<vector<Token>> temp.
*			Once all the Tokens have been saved, it will check if any of them are
*			keywords and change their type if true. Finally it will print
*			The entire list of tokens.
**************************************************************/
void Tokenizer::Tokenize()
{
	try
	{
		//use ifstream to pass in filename
		ifstream File("myFile2.txt");

		//try to open file, throw exception if not
		if (!File)
			throw fileOpenFailure_;

		string line;	//string to hold line from file
		string buf;		//buffer string
		vector<string> tempTokens = vector<string>(); //vector of tempTokens with whitespace removed
		StateMachine stateMachine("combinedState2.txt");	//create an instance of the StateMachine

		//use getline and pass to stringstream(line)
		while (!File.eof())
		{
			getline(File, line);
			stringstream ss(line);

			//add all tokens and remove whitespace
			while (ss >> buf)
				tempTokens.push_back(buf);
		}

		File.close();	//close file

		//Copy vector<Tokens> from stateMachine to vector<vector<Token>> temp
		vector<vector<Token>> temp = vector<vector<Token>>();
		for (unsigned int i = 0; i < tempTokens.size(); i++)
		{
			temp.push_back(stateMachine.testString(tempTokens[i]));
		}

		//Check for Keywords & Colors
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			for (unsigned int j = 0; j < temp[i].size(); j++)
			{
				vector<string>::iterator result;
				result = find_if(m_keywords.begin(),
					m_keywords.end(), bind2nd(isKeyword(), temp[i][j].getVar()));
				if (result != m_keywords.end())
					temp[i][j].setType(*result);
				result = find_if(m_colors.begin(),
					m_colors.end(), bind2nd(isColor(), temp[i][j].getVar()));
				if (result != m_colors.end())
					temp[i][j].setType("colorcode");
			}
		}

		//Print Tokens & save to file
		for (unsigned int i = 0; i < temp.size(); i++) {
			for (unsigned int j = 0; j < temp[i].size(); j++)
				cout << left << setw(20) << temp[i][j].getVar() << " " << temp[i][j].getType() << endl;
		}


	}
		

	catch (int e)	//catch thrown exception, output exception error
	{
		cout << "Error number : " << e << ", File not found" << endl;
	}
}

//Constructor. Call setKeywords(), and Tokenize().
Tokenizer::Tokenizer()
{
	setKeywords();
	setColors();
	Tokenize();
}