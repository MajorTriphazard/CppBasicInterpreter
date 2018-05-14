#include "LetStatement.h"

LetStatement::LetStatement(std::string argument, std::map<std::string, int>& variables)
{
	int lineNumber;
	std::string arg1, arg2;
	std::stringstream commandStream(argument);
	//Extracting Current Line Number, argument, and Input Variable
	commandStream >> lineNumber >> std::ws >> arg1 >> std::ws >> arg2 >> std::ws;

	_arg1 = arg1;
	_arg2 = arg2;
}

LetStatement::~LetStatement() {}

bool LetStatement::Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	LetOperator(LineList, variables, iterator);
	iterator++;
	return true;
}

void LetStatement::LetOperator(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	std::string eq_op;

	_var1 = _arg2.substr(0, 1);
	eq_op = _arg2.substr(1, 1);
	_var2 = _arg2.substr(2, 1);
	_operator = _arg2.substr(3, 1);
	_var3 = _arg2.substr(4, 1);
	IsVar(LineList, variables, iterator, _var1, _var2, _var3);
	LetOperation(LineList, variables, iterator);
}

void LetStatement::IsVar(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator, std::string A, std::string B, std::string C)
{
	// Creating iterator to search current map of variables
	std::map<std::string, int>::iterator it;
	it = variables.find(A);

	//Checking if input variable exists, changing the value if it does, creating it if it doesn't
	if (it == variables.end())
	{
		throw ExceptionSyntaxError("Variable " + A + " does not exist.", "");
	}
	it = variables.find(B);

	//Checking if input variable exists, changing the value if it does, creating it if it doesn't
	if (it == variables.end())
	{
		throw ExceptionSyntaxError("Variable " + B + " does not exist.", "");
	}

	it = variables.find(C);

	//Checking if input variable exists, changing the value if it does, creating it if it doesn't
	if (it == variables.end())
	{
		throw ExceptionSyntaxError("Variable " + C + " does not exist.", "");
	}
}

void LetStatement::LetOperation(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	int i, j, k;
	if (_operator == "+")
	{
		j = variables[_var2];
		k = variables[_var3];
		i = j + k;
		//std::cout << "i= " << i << " j= " << j << " k= " << k << std::endl;
		variables[_var1] = i;
	}
	else if (_operator == "*")
	{
		j = variables[_var2];
		k = variables[_var3];
		i = j * k;
		std::cout << "i= " << i << " j= " << j << " k= " << k << std::endl;
		variables[_var1] = i;
	}
	else if (_operator == "/")
	{
		j = variables[_var2];
		k = variables[_var3];
		i = j / k;
		//std::cout << "i= " << i << " j= " << j << " k= " << k << std::endl;
		variables[_var1] = i;
	}
	else if (_operator == "-")
	{
		j = variables[_var2];
		k = variables[_var3];
		i = j - k;
		//std::cout << "i= " << i << " j= " << j << " k= " << k << std::endl;
		variables[_var1] = i;
	}
	else
	{
		throw ExceptionSyntaxError("Invalid Operation", "");
	}
}