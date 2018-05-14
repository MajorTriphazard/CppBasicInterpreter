#include "ifStatement.h"


ifStatement::ifStatement(std::string commandString, std::map<std::string, int>& variables)
{
	int lineNumber;
	std::string opType, nextBit, arg1, arg2,then;
	char op;
	std::stringstream commandStream(commandString);
	commandStream >> lineNumber >> opType >> nextBit >> then;
	//this is a syntax error in basic i think?
	if (then != "THEN") {
		throw ExceptionSyntaxError("ERROR: Syntax error at line: " + std::to_string(lineNumber), commandString);
	}
	// determine which operator
	if (nextBit.find("=") != std::string::npos) {
		size_t a = nextBit.find("=");
		op = '=';
		arg1 = nextBit.substr(0, a);
		arg2 = nextBit.substr(a + 1, nextBit.size());
	}
	else if (nextBit.find("<") != std::string::npos) {
		size_t a = nextBit.find("<");
		op = '<';
		arg1 = nextBit.substr(0, a);
		arg2 = nextBit.substr(a + 1, nextBit.size());
	}
	else if (nextBit.find(">") != std::string::npos) {
		size_t a = nextBit.find(">");
		op = '>';
		arg1 = nextBit.substr(0, a);
		arg2 = nextBit.substr(a + 1, nextBit.size());
	}
	else {
		arg1 = "";
		arg2 = "";
		op = ' ';
		//Syntax error of some form
		throw ExceptionSyntaxError("ERROR: unknown syntax at line: " + std::to_string(lineNumber), commandString);
	}
	//check if arg1 is a variable or number
	if (!variables.count(arg1))
	{
		try
		{
			std::size_t lastChar;
			int value = std::stoi(arg1, &lastChar);
			_arg1Num = true;
		}
		catch (std::invalid_argument&)
		{
			std::string Errorstring;
			Errorstring = "ERROR: Variable " + arg1 + " does not exist. At line: " + std::to_string(lineNumber);
			throw ExceptionSyntaxError(Errorstring, commandString);
		}
	}
	else{
		_arg1Num = false;
	}
	//check if arg2 is a variable or number
	if (!variables.count(arg2))
	{
		try
		{
			std::size_t lastChar;
			int value = std::stoi(arg2, &lastChar);
			_arg2Num = true;
		}
		catch (std::invalid_argument&)
		{
			std::string Errorstring;
			Errorstring = "ERROR: Variable " + arg2 + " does not exist. At line: " + std::to_string(lineNumber);
			throw ExceptionSyntaxError(Errorstring, commandString);
		}
	}
	else {
		_arg2Num = false;
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
	int valArg1, valArg2;
	bool isTrue = false;
	//if arg1 is number then get its value, otherwise get its value from variable map
	if (_arg1Num)
	{
		std::stringstream temp(_arg1);
		temp >> valArg1;
	}
	else
	{
		valArg1 = variables[_arg1];
	}

	//if arg2 is number then get its value, otherwise get its value from variable map
	if (_arg2Num)
	{
		std::stringstream temp(_arg2);
		temp >> valArg2;
	}
	else
	{
		valArg2 = variables[_arg2];
	}
	// perform the calc
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
		throw ExceptionRuntimeError("Unknown error at line:" + std::to_string(iterator), "");
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