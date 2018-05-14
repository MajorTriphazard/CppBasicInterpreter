#include "printStatement.h"

// Implementation of printStatement.h class
PrintStatement::PrintStatement(std::string argument, std::map<std::string, int>& variables)
{
	line = argument;
	std::size_t quotesStart = argument.find('\"');
	
	// Checks if the arguments has quotes (") in it to dtermine whether it is a string or variable
	if (quotesStart == std::string::npos)
	{
		isStringLiteral = false;
		std::string command = "PRINT ";
		std::size_t commandLocation = argument.find(command) + (unsigned)command.length();
		_value = argument.substr(commandLocation, (unsigned)argument.length() - commandLocation);
	}
	else
	{
		isStringLiteral = true;
		quotesStart++;

		// Finds the close quotes, throwing an exception if it cannot find them
		std::size_t quotesEnd = argument.find('\"', quotesStart);
		if (quotesEnd == std::string::npos)
		{
			_value = "ERROR";
			throw ExceptionSyntaxError("Missing quotes in line: ", line);
		}
		else
		{
			// Separates the string to print from the surrounding quotes
			_value = argument.substr(quotesStart, quotesEnd - quotesStart);
		}
	}
}

PrintStatement::~PrintStatement()
{

}

bool PrintStatement::Run(std::map<int, LineNode*>& LineList, std::map<std::string, int>& variables, int& iterator)
{
	if (isStringLiteral)
	{
		// Check for any newline characters and if they exist then print a new line
		std::string value = _value;
		size_t pos = 0;
		std::string temp, newLine;
		newLine = "\\n";
		while ((pos = value.find(newLine)) != std::string::npos)
		{
			temp = value.substr(0, pos);
			std::cout << temp << std::endl;
			value.erase(0, pos + newLine.length());
		}

		// Print remaining
		std::cout << value;
	}
	else
	{
		// Finds the appropriate variable to print, throwing an exception if it doesn't exist
		std::map<std::string, int>::iterator toPrint = variables.find(_value);
		if (toPrint == variables.end())
		{
			throw ExceptionRuntimeError(_value + " does not exist", line);
			return false;
		}

		std::cout << toPrint->second;
	}
	iterator++;
	return true;
}