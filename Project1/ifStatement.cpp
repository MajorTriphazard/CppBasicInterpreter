#include "ifStatement.h"


ifStatement::ifStatement(std::string commandString, std::map<std::string, int>& variables)
{
	int lineNumber;
	std::string opType,nextBit,arg1,arg2;
	char op;
	std::stringstream commandStream(commandString);
	commandStream >> lineNumber >> opType;
	std::string remainder;
	try
	{
		std::string remainder(commandStream.str().substr(commandStream.tellg()));
		for (std::string::size_type i = 0; i < remainder.size(); ++i)
		{
			if (!isspace(remainder[i]))
			nextBit += remainder[i];
		}
	}
	catch(std::out_of_range n)
	{
		std::cout << "Error invalid syntax at line " << lineNumber << std::endl;
	}

	if (nextBit.find("=") != std::string::npos) {
		size_t a = nextBit.find("=");
		op = '=';
		arg1 = nextBit.substr(0, a);
		arg2 = nextBit.substr(a+1, nextBit.size());
	}
	else if (nextBit.find("<") != std::string::npos) {
		size_t a = nextBit.find("<");
		op = '<';
		arg1 = nextBit.substr(0, a);
		arg2 = nextBit.substr(a+1, nextBit.size());
	}
	else if (nextBit.find(">") != std::string::npos) {
		size_t a = nextBit.find(">");
		op = '>';
		arg1 = nextBit.substr(0, a);
		arg2 = nextBit.substr(a+1, nextBit.size());
	}
	else {
		arg1 = "";
		arg2 = "";
		op = ' ';
		//Syntax error of some form
		std::cout << "ERROR unknown syntax at line: " << lineNumber << std::endl;
		throw ExceptionSyntaxError();
	}

	if (!variables.count(arg1)) 
	{
		std::cout << "Variable " << arg1 << " does not exist" << std::endl;
	}
	_arg1 = arg1;
	_arg2 = arg2;
	_op = op;
}

ifStatement::~ifStatement()
{
}


void ifStatement::setEndIf(int endIfLine) {
	_endIfLineNumber = endIfLine;
}




bool ifStatement::Run(std::map<int, LineNode*>& linelist, std::map<std::string, int>& variables, int& iterator)
{
	int valArg1 = variables[_arg1];
	std::stringstream temp(_arg2);
	int valArg2;
	bool isTrue = false;
	temp >> valArg2;
	switch (_op) {
		case '=':
			isTrue = (valArg1 == valArg2);
			break;
		case '<':
			isTrue = (valArg1 < valArg2);
			break;
		case '>':
			isTrue = (valArg1 > valArg2);
			break;
		default:
			//should never get here!
			break;
	}

	if (!isTrue) {
		iterator = _endIfLineNumber;
	}
	else
	{
		iterator++;
	}
	return true;
}