#include "Handler.h"



int main() 
{
	Handler* handleThis = new Handler();
	std::ifstream myfile("C:\\Users\\Michael Taricone\\source\\repos\\CppBasicInterpreter\\Project1\\Text3.txt");
	// std::ifstream myfile("C:\\Users\\scott\\Documents\\C++BasicInterpreter\\Project1\\Text.txt");
	*handleThis >> myfile;
	handleThis->executeProgram();
	std::cin.get();
}