#include "GoToStatement.h"

GoToStatement::GoToStatement(std::string argument, std::map<std::string, int>& variables)
{
	int lineNumber, GoToLine;
	std::string arg1;
	std::stringstream commandStream(argument);
	// Extracting lineNumber, GoTo argument and GoTo line
	commandStream >> lineNumber >> std::ws >> arg1 >> std::ws >> std::ws >> GoToLine;
	
	setGoTo(GoToLine);
}

GoToStatement::~GoToStatement()
{
}

bool GoToStatement::Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	// Checking if provided GoTo Line Number exists, throwing exception if it doesn't
	if ((LineList).count(_GoToLineNumber) == 1)
	{
		iterator = _GoToLineNumber;
		return true;
	} 
	else
	{
		throw ExceptionRuntimeError("Invalid Input.","At line: "+ std::to_string(iterator));
	}
	return false;
}

void GoToStatement::setGoTo(int GoToLine)
{
	_GoToLineNumber = GoToLine;
}
