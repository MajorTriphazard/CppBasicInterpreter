#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "ExceptionSyntaxError.h"
#include "ExceptionRuntimeError.h"

// Base class for the ifferent comman classes, allowing for the overriding of Run()
class LineNode
{
public:
	virtual ~LineNode() {}

	virtual bool Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator) = 0;
};
