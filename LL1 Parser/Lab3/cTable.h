#ifndef CTABLE_H
#define CTABLE_H

#include <string>
#include <vector>

class cTable
{
public:
	//Constructors
	cTable(const std::string row, const std::string col, const std::vector<std::string> rule);

	//Getters
	const std::vector<std::string>& getRule(void);
	const std::string getRow(void);
	const std::string getCol(void);

	//Setters
	void setRule(const std::string rule);
	void setRow(const std::string row);
	void setCol(const std::string col);

private:
	//Private members variables
	std::vector<std::string> m_rule;
	std::string m_col;
	std::string m_row;
};

#endif