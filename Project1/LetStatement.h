#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "LineNode.h"

class LetStatement : public LineNode
{
public:
	std::string _arg1, _arg2, _operator;
	std::string _var1, _var2, _var3;
	LetStatement(std::string, std::map<std::string, int>&);
	~LetStatement();
	bool Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator);
	void LetOperator(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator);
	void IsVar(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator, std::string, std::string, std::string);
	void LetOperation(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator);
};
