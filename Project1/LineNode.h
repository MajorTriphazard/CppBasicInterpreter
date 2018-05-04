#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>

class LineNode
{
public:
	virtual ~LineNode() {}

	virtual bool Run(std::map<int, LineNode*>& LineList, std::map<char, int>& variables, std::map<int, LineNode*>::iterator& iterator) = 0;
};
