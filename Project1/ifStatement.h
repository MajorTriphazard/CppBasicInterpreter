#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "LineNode.h"

//using namespace std;

class ifStatement : public LineNode
{
public:
	int _endIfLineNumber;
	std::string _arg1, _arg2;
	bool _arg1Num, _arg2Num;
	char _op;
	ifStatement(std::string, std::map<std::string, int>&);
	~ifStatement();
	void setEndIf(int endIfLine);
	bool Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator);
};
