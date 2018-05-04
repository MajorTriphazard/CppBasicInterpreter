#include "Handler.h"
#include "ifStatement.h"


Handler::Handler()
{
	variables = new map<char, int>;
}

Handler::~Handler(){}

bool Handler::operator>>(istream &input)
{
	string line;
	int lineNumber;
	string opType;
	stack<int> ifStack;
	while (getline(input, line)) 
	{
		stringstream lineStream(line);
		lineStream >> lineNumber >> opType;
		transform(opType.begin(), opType.end(), opType.begin(), ::toupper);
		if (opType == "IF")
		{
			ifStatement* myIf = new ifStatement(line);
			ifStack.push(lineNumber);
				//create if statement class
		}
		if (opType == "ENDIF")
		{
			if (ifStack.size() > 0)
			{
				int ifLine = ifStack.top();
				ifStack.pop();
				cout << "found End if for " << ifLine << " at: " << lineNumber << endl;
			}
			else
			{
				cout << "Error: no matching if for this end if at line: " << lineNumber << endl;
				// error end line found but no if statment matches
			}
		}
		if (opType == "INPUT")
		{

		}
		if (opType == "LET")
		{
		}
		if (opType == "PRINT")
		{

		}



		cout << lineNumber<< " " << opType << endl;
	}
	if (ifStack.size() != 0)
	{
		cout << "Error: end if not found for IF line: " << ifStack.top() << endl;
	}
	return true;
}