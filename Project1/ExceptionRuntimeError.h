#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
class ExceptionRuntimeError
{
public:
	std::string lineContents;
	std::string errorMessage;
	ExceptionRuntimeError(std::string, std::string);
	~ExceptionRuntimeError();
};

