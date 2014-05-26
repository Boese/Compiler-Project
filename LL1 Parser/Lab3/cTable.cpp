#include "cTable.h"

using namespace std;

/**************Constructors******************/
cTable::cTable(const string row, const string col, const vector<string> rule) : m_rule(rule), m_row(row), m_col(col)
{
}

/**************Getters******************/
const string cTable::getCol(void) { return this->m_col; }

const string cTable::getRow(void) { return this->m_row; }

const vector<string>& cTable::getRule(void) { return this->m_rule; }

/**************Setters******************/
void cTable::setCol(string col) { this->m_col = col; }

void cTable::setRow(string row) { this->m_row = row; }

void cTable::setRule(string rule) { this->m_rule.push_back(rule); }