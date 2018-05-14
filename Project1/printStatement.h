#pragma once
#include <string>
#include <map>
#include <vector>
#include "LineNode.h"

class PrintStatement : public LineNode
{
public:
	PrintStatement(std::string, std::map<std::string, int>&);
	~PrintStatement();

	bool isStringLiteral;
	std::string line;
	std::string _value;
	bool Run(std::map<int, LineNode*>&, std::map<std::string, int>&, int&);
};