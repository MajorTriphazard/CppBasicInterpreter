#include "ifStatement.h"

ifStatement::ifStatement(std::string commandString, std::map<std::string, int>& variables)
{
	int lineNumber;
	std::string opType,nextBit,arg1,arg2;
	char op;
	std::stringstream commandStream(commandString);
	commandStream >> lineNumber >> opType;
	commandStream >> nextBit;
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
		std::cout << "DID I GET HERE? " << nextBit << std::endl;
		//not sure of this case
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
	bool isTrue;
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
	return true;
}