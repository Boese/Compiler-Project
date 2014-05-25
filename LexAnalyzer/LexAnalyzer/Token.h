/************************************************************************
* Class: Token
*
* Constructors:
*	Token(string var, string type) : m_var(var), m_type(type) {}
*		Takes a string var and string type. Set both member variables
*
* Mutators:
*		void setType(const string& type) { m_type = type; }
*			Allows change of type with passed in string type
*
* Methods:
*	const string getType() { return m_type; }
*	const string getVar() { return m_var; }
*
*************************************************************************/

#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <iostream>

using namespace std;

class Token
{
public:
	Token(string var, string type) : m_var(var), m_type(type) {}

	const string getType() { return m_type; }
	const string getVar() { return m_var; }

	void setType(const string& type) { m_type = type; }
private:
	string m_type;
	string m_var;
};

#endif