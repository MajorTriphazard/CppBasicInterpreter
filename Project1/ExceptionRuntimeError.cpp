#include "ExceptionRuntimeError.h"



ExceptionRuntimeError::ExceptionRuntimeError(std::string errMsg, std::string line)
{
	errorMessage = errMsg;
	lineContents = line;
}


ExceptionRuntimeError::~ExceptionRuntimeError()
{
}
