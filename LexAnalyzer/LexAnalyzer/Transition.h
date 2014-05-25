/************************************************************************
* Class: Transition
*
* Constructors:
*	Transition(const int &start = 0)
*		m_start is initialized to 0.
*
* Mutators:
*	friend  istream  &operator>>(istream &in, Transition &rhs)
*		This overloaded operator overloads the istream >> operator.
*		Used for setting the start state, the vector<char>, and end state
*
* Methods:
*	const int &getStart() const
*		This method will return m_start
*	const int &getEnd() const
*		This method will return m_end
*	const vector<char> &getAllLetters()
*		This method will return a vector of chars
*************************************************************************/
#ifndef TRANSITION_H
#define TRANSISTION_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Transition
{
	//overload istream operator>>
	friend  istream  &operator>>(istream &in, Transition &rhs);

public:
	//constructor, initialize m_start to 0
	Transition(const string  &start = "Start") : m_start(start) {}

	//getters, returns start state, end state, or vector of chars
	const string &getStart() const { return m_start; }
	const string &getEnd() const { return m_end; }
	const vector<char> &getAllLetters() const { return m_letters; }

private:
	vector<char> m_letters;		//contains list of accepted chars for transition
	string m_start;	//The start state integer
	string m_end;		//The end state integer
};
#endif