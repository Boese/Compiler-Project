/************************************************************************
* Class: StateMachine
*
* Constructors:
*	StateMachine(const string& filename)
*		m_currentState and m_fileFound are initialized to 0 and false.
*		Is responsible to read in file and copy the Valid states to member variable
*		vector<int> m_validStates. Also reads in every transition to vector<Transition>
*		m_transitions.
*
* Mutators:
*		vector<Token> testString(string userString)
*			This method will take a string from Tokenizer and return
*			a vector<Token>
*
*		const string getNext(string currentState, const char &character)
*			This will take a currentState string, and char and return
			the future state.
*
* Methods:
*	const string testString(const string& userString)
*		This method will use two helper functions to determine
*		if user string is valid or not.
*	const bool fileFound()
*		This method returns m_fileFound.
*************************************************************************/


#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <string>
#include "Transition.h"
#include "Token.h"

using namespace std;

class StateMachine
{
public:
	StateMachine(const string& filename);	//constructor
	vector<Token> testString(const string &userString);	//check is user string is valid
	const string getNext(string currentState, const char &character);	//return future state based on input
	const bool fileFound() const { return m_fileFound; }	//return m_fileFound

private:
	string m_currentState;	//current state
	bool m_fileFound;	//boolean if file was found or not

	//vector to hold valid states
	typedef vector<string> finalStates;
	finalStates m_validStates;

	//vector to hold Transitions
	typedef vector<Transition> transitions;
	transitions m_transitions;
};
#endif