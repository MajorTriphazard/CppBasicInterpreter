#include "printStatement.h"


PrintStatement::PrintStatement(std::string argument, std::map<std::string, int>& variables)
{
	line = argument;
	std::size_t quotesStart = argument.find('\"');
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
		std::size_t quotesEnd = argument.find('\"', quotesStart);
		if (quotesEnd == std::string::npos)
		{
			_value = "Missing quotes";
		}
		else
		{
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
		//std::string value = _value;
		//size_t pos = 0;
		//std::string temp;
		//while ((pos = value.find("\\N")) != std::string::npos) {
		//	temp = value.substr(0, pos);
		//	std::cout << temp << std::endl;
		//	value.erase(0, pos + 2);
		//}
		std::cout << _value << std::endl;
	}
	else
	{
		std::map<std::string, int>::iterator toPrint = variables.find(_value);
		if (toPrint == variables.end())
		{
			throw ExceptionRuntimeError(_value + " does not exist", line);
			return false;
		}

		std::cout << toPrint->second << std::endl;
	}
	iterator++;
	return true;
}