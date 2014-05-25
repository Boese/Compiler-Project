#include "StateMachine.h"
#include "Token.h"
#include <string>
#include <cstring>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <functional>

#define fileOpenFailure_ 1	//file not opened exception 1

using namespace std;

//pass in 2 filenames, state machine and string
StateMachine::StateMachine(const string& filename) : m_currentState("Start"), m_fileFound(false)
{
	try
	{
		//use istream iterator to read in transitions
		//use ifstream to pass in filename
		typedef  istream_iterator<Transition>  InIter;
		ifstream File(filename);

		//try to open file, throw exception if not
		if (!File)
			throw fileOpenFailure_;

		m_fileFound = true;	//set m_fileFound to true

		//read in final states
		string line;	//string to hold line from file

		//use getline and pass to istringstream(line)
		getline(File, line);
		istringstream iss(line);

		//STL copy function, copy all valid states into vector<int> m_validStates
		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(m_validStates));

		//STL copy function, copy all Transitions into vector<Transition> m_transitions
		//uses overloaded istream >> in Transition.cpp
		copy(InIter(File),
			InIter(),
			inserter(m_transitions, m_transitions.end()));

		File.close();	//close file
	}
	catch (int e)	//catch thrown exception, output exception error
	{
		cout << "Error number : " << e << ", File not found" << endl;
	}
}

//******Helper functions: These binary_functions are used to help StateMachine::testString()*****//

//returns true if currentState is equal to the transition start state
struct  matchState : public  binary_function<Transition, string, bool>
{
	bool  operator()(const Transition  &transition, const string  &currentState)  const
	{
		//return true if transition start state is equal to m_currentState
		if (transition.getStart().compare(currentState) == 0)
			return true;
		return false;
	}
};

//returns true if the userChar matches one of the transitions.getAllLetters()
struct  matchChar : public  binary_function<Transition, char, bool>
{
	bool  operator()(const Transition  &transition, const char  &userChar)  const
	{
		for (unsigned int i = 0; i < transition.getAllLetters().size(); i++)
		{
			//returns true if userChar is equal to any letter in passed in transition
			if (transition.getAllLetters()[i] == userChar)
				return true;
		}

		return false;
	}
};

//*********************************************************************************//

/**************************************************************
*   Entry:  String currentState, and char character
*
*    Exit:  Return new currentState, based on input
*
* Purpose:  This function will check what the next state
*			will be based on the currentState, and current character
*			passed in. Helper function for testString().
**************************************************************/

const string StateMachine::getNext(string currentState, const char& character) {

	//create a temporary vector of applicable transitions
	typedef vector<Transition> temp;
	temp tempVec;

	//STL copy to make a temp vector with only the transitions that include the currentstate
	copy_if(m_transitions.begin(),
		m_transitions.end(),
		inserter(tempVec, tempVec.end()),
		bind2nd(matchState(), currentState));

	//STL find to find the transition that matches the userString[i] character
	vector<Transition>::iterator result;
	result = find_if(tempVec.begin(),
		tempVec.end(),
		bind2nd(matchChar(), character));

	//If found change currentState
	if (result != tempVec.end())
	{
		currentState = result->getEnd();
	}
	return currentState;
}

//*********************************************************************************//

/**************************************************************
*   Entry:  String
*
*    Exit:  Return vector<Token>
*
* Purpose:  This function will take a string that has no whitespace
*			inside of it from the Tokenizer. It will loop until
*			userString.length(). It uses the function getNext()
*			to tell what the next state will be based on the current
*			state and userString[i]. 
*
*			Once it hits an Operator or Symbol, it saves the current
*			token, and resets the temp_Token string. When complete
*			it will save the last Token and return the vector<Token>
**************************************************************/
vector<Token> StateMachine::testString(const string &userString)
{
	vector<string> temp = vector<string>();
	m_currentState = "Start";		//set currentstate to Start

	vector<Token> tokens = vector<Token>();	//hold tokens
	string temp_Token;	//hold single token 
	unsigned int temp_Token_Counter = 0;

	//loop through every character of userString
	for (unsigned int i = 0; i < userString.length(); i++)
	{
		//	if next state is Operator
		if (getNext(m_currentState, userString[i]).compare("Operator") == 0)
		{
			//make sure temp_Token isn't empty
			//append current token
			if (temp_Token.length() > 0)
				tokens.push_back(Token(temp_Token, m_currentState));

			temp_Token_Counter = 0;	//set counter to 0

			//check if token is single or double operator(++)
			if (getNext(m_currentState, userString[i + 1]).compare("Operator") == 0) {
				tokens.push_back(Token(userString.substr(i, 2), "Operator")); i++;
			}
			else
				tokens.push_back(Token(userString.substr(i, 1), "Operator"));

			temp_Token.clear(); continue;	//clear temp_Token and continue
		}

		//	if next state is a symbol 
		if (getNext(m_currentState, userString[i]).compare("Symbol") == 0)
		{
			//make sure temp_Token isn't empty
			//append current token
			if (temp_Token.length() > 0)
				tokens.push_back(Token(temp_Token, m_currentState));

			temp_Token_Counter = 0;	//set counter to 0
			tokens.push_back(Token(userString.substr(i, 1), "Symbol")); //append Symbol Token
			temp_Token.clear(); continue;	//clear temp_Token and continue
		}

		//get the currentState
		m_currentState = getNext(m_currentState, userString[i]);

		//append temp_Token
		if (userString.length() > 0){
			temp_Token.append(userString.substr(i, 1));
			temp_Token_Counter++;
		}
	}
	//add temp_Token
	if (temp_Token.length() > 0)
		tokens.push_back(Token(temp_Token, m_currentState));
	return tokens;
}