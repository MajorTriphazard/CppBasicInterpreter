#pragma once
#include <iostream>
#include <sstream>
#include <string>


class ExceptionSyntaxError
{
public:
	std::string lineContents;
	std::string errorMessage;
	ExceptionSyntaxError(std::string, std::string);
	~ExceptionSyntaxError();
};

