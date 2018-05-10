#pragma once
#include <iostream>
#include <sstream>
#include <string>


class ExceptionSyntaxError
{
public:
	int line;
	std::string lineContents;
	std::string errorMessage;
	ExceptionSyntaxError();
	~ExceptionSyntaxError();
};

