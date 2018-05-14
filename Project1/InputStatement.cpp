#include "InputStatement.h"
#include <map>

InputStatement::InputStatement(std::string argument, std::map<std::string, int>& variables)
{
	int lineNumber;
	std::string arg1,input;
	std::stringstream commandStream(argument);

	//Extracting Current Line Number, argument, and Input Variable
	commandStream >> lineNumber >> std::ws >> arg1 >> std::ws >> std::ws >> input >> std::ws;
	//Setting Input Variable
	_input = input;
	// Creating iterator to search current map of variables
	std::map<std::string, int>::iterator it;
	it = variables.find(_input);
	//Checking if input variable exists, changing the value if it does, creating it if it doesn't
	if (it == variables.end())
	{
		variables.insert(std::pair<std::string, int>(_input, 0));
	}
}

InputStatement::~InputStatement() {}

bool InputStatement::Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	int input;
	// Obtaining value for variable
	std::cin >> input;
	// If input is invalid throw an error
	if (!std::cin) {
		std::cout << "Invalid Input: not an integer." << std::endl;
		throw ExceptionRuntimeError("Invalid Input : not an integer.", "");
	}

	// Creating iterator to search current map of variables
	std::map<std::string, int>::iterator it;
	it = variables.find(_input);

	//Checking if input variable exists, changing the value if it does, creating it if it doesn't
	if (it != variables.end())
	{
		it->second = input;
	}
	else
	{
		variables.insert(std::pair<std::string, int>(_input, input));
	}
	iterator++;

	return true;
}

