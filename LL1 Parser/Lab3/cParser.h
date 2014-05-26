#ifndef CPARSER_H
#define CPARSER_H

#include "cTable.h"
#include "RDP.h"

#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

class cParser
{
public:
	//Constructor
	cParser();

	void addTableEntry(const std::string entry);
	void addInputEntry(const std::string input);
	void startRule(const std::string rule);
	void writeTree(const std::string entry, int col);
	bool parse(const std::string rule);

private:
	//Private members
	std::vector<cTable> m_table;
	std::queue<parserEntry> m_input;
	std::stack<std::string> m_stack;
};

#endif