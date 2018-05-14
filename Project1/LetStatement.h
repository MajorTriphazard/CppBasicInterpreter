#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "LineNode.h"

class LetStatement : public LineNode
{
public:
	std::string _arg1, _arg2;
	std::string _var1, _var2, _var3;
	bool _var2Num, _var3Num, _2vars;
	char  _operator;

	LetStatement(std::string, std::map<std::string, int>&);
	~LetStatement();
	bool Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator);
	};
