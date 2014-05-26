#include "cParser.h"
#include <iostream>
#include <sstream>
#include <fstream>

#define fileOpenFailure_ 0;		// Execption Handler

using namespace std;

cParser::cParser()
{
	m_stack.push("$");
}

void cParser::addTableEntry(const string entry)
{
	string row, col;
	vector<string> rules;
	stringstream iss(entry);

	iss >> row >> col;

	while (iss)
	{
		string temp, token;
		if(!getline(iss, temp, ';')) break;
		stringstream ss(temp);
		ss >> temp;
		rules.push_back(temp);
	}

	m_table.push_back(cTable(row, col, rules));
}

void cParser::addInputEntry(const string input)
{
	string token, type;
	stringstream iss(input);

	while (iss)
	{
		iss >> token >> type;
	}
	m_input.push(parserEntry(token, type));
}

void cParser::startRule(const string rule)
{
	m_stack.push(rule);
}

void cParser::writeTree(const string entry, int col)
{
	// Open input file stream
	ofstream file;

	file.open("tree.txt", ofstream::app);

	// Oops something went wrong.
	if (!file)
		throw fileOpenFailure_;

	file << col << ", " << entry << "\n";

	file.close();
}

bool cParser::parse(const string rule)
{
	int col = 0;

	startRule(rule);

	cout << m_stack.top() << "col: " << col << endl;
	while (!m_stack.empty() && !m_input.empty())
	{
		//[a, a]
		if (m_stack.top() == m_input.front().m_type)
		{
			//cout << "\n[ " << m_stack.top() << ", " << m_input.front().m_value << " ]"
				//<< " Action: pop stack, pop input.\n" << endl;
			cout << m_input.front().m_value << " col: " << col << endl;
			//writeTree(m_stack.top(), col);
			m_stack.pop();
			m_input.pop();
		}
		//[E, a] -> TX
		//[Y, $] -> lambda
		else
		{
			bool success = false;
			for (auto& iter : m_table)
			{
				if (iter.getRow() == m_stack.top())
				{
					if (iter.getCol() == m_input.front().m_type)
					{
						success = true;
						//cout << "[ " << m_stack.top() << ", " << m_input.front().m_value << " ]" 
							 //<< " Action: pop stack.\n" << endl;
						//cout << m_stack.top() << endl;
						m_stack.pop();
						col--;
						vector<string>::const_reverse_iterator itr = iter.getRule().rbegin();
						for ( ; itr != iter.getRule().rend() ; itr++)
						{
							if (*itr != "lambda")
							{
								col++;
								m_stack.push(*itr);
								//cout << "Pushed " << *itr << " to stack." << endl;
								cout << m_stack.top() << " col: " << col << " ";
							}
							else
							{
								//cout << "lambda case pop stack. Col: " << endl;
								cout << "lambda, col: " << col << " ";
							}
						}
						cout << endl;
						break;
					}
				}
			}
			if (!success)
			{
				cout << "\n[ " << m_stack.top() << ", " << m_input.front().m_value << " ]"
					 << " Action: Failed.\n" << endl;
				cout << "********************Stack Dump*********************\n" << endl;
				while (!m_stack.empty())
				{
					cout << m_stack.top() << endl;
					m_stack.pop();
				}
				cout << "\n********************Input Dump*********************\n" << endl;
				while (!m_input.empty())
				{
					cout << m_input.front().m_value << endl;
					m_input.pop();
				}
				return false;
			}
		}
	}
	return true;
}