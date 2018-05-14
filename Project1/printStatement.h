#pragma once
#include <string>
#include <map>
#include "LineNode.h"

class PrintStatement : public LineNode
{
public:
	PrintStatement(std::string, std::map<std::string, int>&);
	~PrintStatement();

	bool isStringLiteral;
	std::string line;
	std::string value;
	bool Run(std::map<int, LineNode*>&, std::map<std::string, int>&, int&);
};