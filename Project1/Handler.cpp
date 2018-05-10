#include "Handler.h"
#include "ifStatement.h"
#include "printStatement.h"
#include "GoToStatement.h"
#include "InputStatement.h"
#include "LetStatement.h"


Handler::Handler()
{
	_variables = new std::map<std::string, int>;
	_lineList = new	std::map<int, LineNode*>;
	_iterator = 0;
}

Handler::~Handler(){}

bool Handler::operator>>(std::istream &input)
{
	try 
	{
		std::string line;
		int lineNumber;
		std::string opType;
		std::stack<int> ifStack;
		while (getline(input, line))
		{
			std::stringstream lineStream(line);
			lineStream >> lineNumber >> opType;

			//Line repeated
			if ((*_lineList).count(lineNumber) != 0) {
				std::cout << "Syntax Error, line number: " << lineNumber << " is repeated" << std::endl;
				return false;
			}

			//put all to uppercase for simplicity
			std::transform(opType.begin(), opType.end(), opType.begin(), ::toupper);
			//check which opperator it is
			if (opType == "IF")
			{
				&_lineList->insert(std::pair<int, LineNode*>(lineNumber, new ifStatement(line, *_variables)));
				ifStack.push(lineNumber);
			}
			else if (opType == "ENDIF")
			{
				//check there is a valid if for the end if
				if (ifStack.size() > 0)
				{
					// upon finding end if set respective if's endifline value
					int ifLine = ifStack.top();
					((ifStatement*)(*_lineList)[ifLine])->setEndIf(lineNumber);
					ifStack.pop();
				}
				else
				{
					std::cout << "Error: no matching if for this end if at line: " << lineNumber << std::endl;
					return false;
					// error end line found but no if statment matches
				}
			}
			else if (opType == "INPUT")
			{
				&_lineList->insert(std::pair<int, LineNode*>(lineNumber, new InputStatement(line, *_variables)));
			}
			else if (opType == "LET")
			{
				&_lineList->insert(std::pair<int, LineNode*>(lineNumber, new LetStatement(line, *_variables)));
			}
			else if (opType == "GOTO")
			{
				&_lineList->insert(std::pair<int, LineNode*>(lineNumber, new GoToStatement(line, *_variables)));
			}
			else if (opType == "PRINT")
			{
				&_lineList->insert(std::pair<int, LineNode*>(lineNumber, new PrintStatement(line, *_variables)));
			}
			else {
				std::cout << "Syntax Error at line " << lineNumber << ". Unknown command: " << opType << std::endl;
				return false;
			}
		}
		//if whole program checked and there are unclosed if statements
		if (ifStack.size() != 0)
		{
			std::cout << "Error: end if not found for IF line: " << ifStack.top() << std::endl;
			return false;
		}
		return true;
	}
	catch (ExceptionSyntaxError) 
	{
		std::cout << "We caught an exception" << std::endl;
	}
}

bool Handler::executeProgram() 
{
	try
	{
		while (true)
		{
			if ((*_lineList).count(_iterator) == 1)
			{
				std::cout << "Running line " << _iterator << std::endl;
				(*_lineList)[_iterator]->Run(*_lineList, *_variables, _iterator);
			}
			else
			{
				_iterator++;
			}
		}
		return true;
	}
	catch(ExceptionRuntimeError)
	{
		std::cout << "We caught an exception 2 " << std::endl;
	}
}