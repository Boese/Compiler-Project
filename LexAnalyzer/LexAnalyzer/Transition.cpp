#include "Transition.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**************************************************************
*   Entry:  overloaded istream &in is input
*
*    Exit:  After int i reaches string temp.length()
*
* Purpose:  For every Transition, read in first the start state
*			m_start. Then copy the list of accepted chars to string
*			temp. Then read in end state to m_end.
*
*			For loop copies all the elements from string temp
*			into the vector m_letters
**************************************************************/

istream  &operator>>(istream  &in, Transition  &rhs)
{
	string temp;	//temporary string for list of accepted chars
	in >> rhs.m_start >> temp >> rhs.m_end;		//input to correct member variables

	rhs.m_letters.clear();	//clear the vector so it doesn't get appended from following Transitions

	//copy string temp into vector<char> m_letters
	for (unsigned int i = 0; i < temp.length(); i++)
		rhs.m_letters.push_back(temp[i]);

	return  in;
}