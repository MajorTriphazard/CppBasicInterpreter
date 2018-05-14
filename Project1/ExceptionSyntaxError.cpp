#include "ExceptionSyntaxError.h"



ExceptionSyntaxError::ExceptionSyntaxError(std::string errMsg, std::string line)
{
	errorMessage = errMsg;
	lineContents = line;
}


ExceptionSyntaxError::~ExceptionSyntaxError()
{
}
