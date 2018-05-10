#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
class ExceptionRuntimeError
{
public:
	int line;
	std::string lineContents;
	std::string errorMessage;
	ExceptionRuntimeError();
	~ExceptionRuntimeError();
};

