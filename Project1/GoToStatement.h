#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "LineNode.h"

class GoToStatement : public LineNode
{
public:
	int _GoToLineNumber;
	std::string _arg1;

	GoToStatement(std::string, std::map<std::string, int>&);
	~GoToStatement();
	void setGoTo(int GoToLine);
	bool Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator);
}; 
