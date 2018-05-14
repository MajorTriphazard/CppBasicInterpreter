#include "LetStatement.h"

LetStatement::LetStatement(std::string argument, std::map<std::string, int>& variables)
{
	int lineNumber;
	std::string letarg, arg1, arg2, op, eq_op, variable1, part2;
	std::stringstream commandStream(argument);
	//Extracting Current Line Number, Let and operation that needs to be performed (i.e. A=B*2)
	commandStream >> lineNumber >> std::ws >> letarg >> std::ws >> _arg2 >> std::ws;

	// Finding the '=' Operator. Everything before is the first variable, everything after is part2. 
	if (_arg2.find("=") != std::string::npos) {
		size_t a = _arg2.find("=");
		eq_op = '=';
		variable1 = _arg2.substr(0, a);
		part2 = _arg2.substr(a + 1, _arg2.size());
		_2vars = true;
		// Finding the Operator between the variables, if there is one the _2vars is set to true meaning there are 2 variables
		if (part2.find("+") != std::string::npos) {
			size_t a = part2.find("+");
			_operator = '+';
			arg1 = part2.substr(0, a);
			arg2 = part2.substr(a + 1, part2.size());
		}
		else if (part2.find("*") != std::string::npos) {
			size_t a = part2.find("*");
			_operator = '*';
			arg1 = part2.substr(0, a);
			arg2 = part2.substr(a + 1, part2.size());
		}
		else if (part2.find("/") != std::string::npos) {
			size_t a = part2.find("/");
			_operator = '/';
			arg1 = part2.substr(0, a);
			arg2 = part2.substr(a + 1, part2.size());
		}
		else if (part2.find("-") != std::string::npos) {
			size_t a = part2.find("-");
			_operator = '-';
			arg1 = part2.substr(0, a);
			arg2 = part2.substr(a + 1, part2.size());
		}
		else
		{
			// If no operator is found, _2vars is set to false-> signifying only 1 variable is present
			arg1 = part2;
			_2vars = false;
		}
		try 
		{
			// Checking if the first argument is valid, _var2Num set to true if valid
			std::size_t lastChar;
			int value = std::stoi(arg1, &lastChar);
			_var2Num = true;
			_var2 = arg1;
		}
		catch (std::invalid_argument&)
		{
			// If first argument is invalid, _var2Num set to false.
			_var2Num = false;
			_var2 = arg1;
			// Checking if the variable exists, throwing error if it doesn't
			if (!variables.count(arg1))
			{
				std::string Errorstring;
				Errorstring = "ERROR: Variable " + arg1 + " does not exist. At line: " + std::to_string(lineNumber);
				throw ExceptionSyntaxError(Errorstring, argument);
			}
		}
		try
		{
			// Checking if the second argument is valid, setting _var3Num to true if it is
			std::size_t lastChar;
			int value = std::stoi(arg2, &lastChar);
			_var3Num = true;
			_var3 = arg2;
		}
		catch (std::invalid_argument&)
		{ 
			// _var3Num set to false because argument is invalid
			_var3Num = false;
			_var3 = arg2;
			// Checking if the variable exists, throwing error if it doesn't
			if (!variables.count(arg2))
			{
				std::string Errorstring;
				Errorstring = "ERROR: Variable " + arg2 + " does not exist. At line: " + std::to_string(lineNumber);
				throw ExceptionSyntaxError(Errorstring, argument);
			}
		}
		}
	// Setting the output variable
	_var1 = variable1;	
}

LetStatement::~LetStatement() {}

bool LetStatement::Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	int valVar2, valVar3;

	// If the first input argument is a valid integer, setting the value to the input
	if (_var2Num)
	{
		std::stringstream temp(_var2);
		temp >> valVar2;
	}
	else
	{
		// Otherwise finding the value from stored variables
		valVar2 = variables[_var2];
	}
	//True if there are 2 variables
	if (_2vars)
	{
		// If second input argument is a valid integer, setting the value to the input
		if (_var3Num)
		{
			std::stringstream temp(_var3);
			temp >> valVar3;
		}
		else
		{
			// Otherwise finding the value from stored variables
			valVar3 = variables[_var3];
		}
		// Performing Operation
		switch (_operator)
		{
		case '+':
			variables[_var1] = valVar2 + valVar3;
			break;
		case '*':
			variables[_var1] = valVar2 * valVar3;
			break;
		case '-':
			variables[_var1] = valVar2 - valVar3;
			break;
		case '/':
			variables[_var1] = valVar2 / valVar3;
			break;	
		}
	}
	else 
	{
		// If no operator is found then only 1 input argument was provided (i.e. A=10 or A=B). Setting output argument to said value.
		variables[_var1] = valVar2;
	}
	iterator++;
	return true;
}

