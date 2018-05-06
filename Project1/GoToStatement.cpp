#include "GoToStatement.h"

GoToStatement::GoToStatement(std::string argument, std::map<std::string, int>& variables)
{
	int lineNumber, GoToLine;
	std::string arg1;
	std::stringstream commandStream(argument);
	commandStream >> lineNumber >> std::ws >> arg1 >> std::ws >> std::ws >> GoToLine;
	
	setGoTo(GoToLine);
}

GoToStatement::~GoToStatement()
{
}

bool GoToStatement::Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	if ((LineList).count(_GoToLineNumber) == 1)
	{
		iterator = _GoToLineNumber;
		return true;
	}
	else
	{
		std::cout << "Line Does Not Exist." << std::endl;
	}
	return false;
}

void GoToStatement::setGoTo(int GoToLine)
{
	_GoToLineNumber = GoToLine;
}
