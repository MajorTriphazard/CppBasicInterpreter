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

Handler::~Handler()
{
	delete _variables;
	// delete pointers to each line class first, then the map
	for (std::map<int, LineNode*>::iterator itr = _lineList->begin(); itr != _lineList->end(); itr++)
	{
		delete itr->second;
	}
	delete _lineList;
}

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
				throw ExceptionSyntaxError("Unknown command at line" + std::to_string(lineNumber), line);
				std::cout << "Unknown command at line" + std::to_string(lineNumber) << std::endl;
				std::cout << line << std::endl;
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
	catch (ExceptionSyntaxError e) 
	{
		std::cout << e.errorMessage << std::endl;
		std::cout << e.lineContents << std::endl;
		return false;
	}
}

bool Handler::executeProgram() 
{
	try
	{
		while (true)
		{
			if ((*_lineList).count(_iterator) >0)
			{
				std::cout << "Running Line " << _iterator << std::endl;
				(*_lineList)[_iterator]->Run(*_lineList, *_variables, _iterator);
				std::cout << "Ran line " << _iterator << std::endl;
			}
			else
			{
				_iterator++;
			}
		}
		return true;
	}
	catch(ExceptionRuntimeError e)
	{
		std::cout << e.errorMessage << std::endl;
		std::cout << e.lineContents << std::endl;
		return false;
	}
}