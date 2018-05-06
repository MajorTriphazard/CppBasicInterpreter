#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "LineNode.h"

class InputStatement : public LineNode
{
public:
	std::string _arg1, _input;
	int _inputValue;
	InputStatement(std::string, std::map<std::string, int>&);
	~InputStatement();
	bool Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator);
	//void IsVariable(std::string argument, std::map<std::string, int>& variables);
};
