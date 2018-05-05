#include "Handler.h"



int main() 
{
	
	Handler* handleThis = new Handler();
	std::ifstream myfile("C:\\Users\\Genna\\source\\repos\\CppBasicInterpreter\\Project1\\Text.txt");
	*handleThis >> myfile;
	handleThis->executeProgram();
	std::cin.get();
}