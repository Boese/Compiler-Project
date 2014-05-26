#ifndef RDP_H
#define RDP_H

#include <string>

struct parserEntry
{
	parserEntry(std::string name, std::string type) { m_value = name; m_type = type; };

	std::string m_value;
	std::string m_type;
};

#endif