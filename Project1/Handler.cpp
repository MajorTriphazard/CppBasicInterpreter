#include "Handler.h"
#include "ifStatement.h"


Handler::Handler()
{
	_variables = new std::map<std::string, int>;
	_lineList = new	std::map<int, LineNode*>;
	_iterator = 0;
}

Handler::~Handler(){}

bool Handler::operator>>(std::istream &input)
{
	std::string line;
	int lineNumber;
	std::string opType;
	std::stack<int> ifStack;
	ifStatement* myIf;
	&_variables->insert(std::pair<std::string, int>("A", 9));
	&_variables->insert(std::pair<std::string, int>("B", 10));
	&_variables->insert(std::pair<std::string, int>("C", 11));
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
			myIf = new ifStatement(line,*_variables);
			ifStack.push(lineNumber);
			&_lineList->insert(std::pair<int, LineNode*>(lineNumber, myIf));
				//create if statement class
		}
		else if (opType == "ENDIF")
		{
			//check there is a valid if for the end if
			if (ifStack.size() > 0)
			{
				// upon finding end if set respective if's endifline value
				int ifLine = ifStack.top();
				ifStack.pop();
				myIf = (ifStatement*)(*_lineList)[ifLine];
				myIf->setEndIf(lineNumber);
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

		}
		else if (opType == "LET")
		{
		}
		else if (opType == "PRINT")
		{

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

bool Handler::executeProgram() {
	while (true)
	{
		if ((*_lineList).count(_iterator) == 1)
		{
			(*_lineList)[_iterator]->Run(*_lineList, *_variables, _iterator);
			std::cout << "Running line " << _iterator << std::endl;
			_iterator++;
		}
		else
		{
			_iterator++;
		}
	}
	return true;
}