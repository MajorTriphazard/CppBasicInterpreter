#include "ifStatement.h"



ifStatement::ifStatement(string commandString)
{
	int lineNumber;
	string opType;
	string nextBit;
	stringstream commandStream(commandString);
	commandStream >> lineNumber >> opType;
	commandStream >> nextBit;
		cout << "MY IF: " << nextBit << endl;
}


ifStatement::~ifStatement()
{
}
