#include "Handler.h"



int main(int argc, char *argv[])
{
	if (argc != 2) 
	{
		std::cout << "Please check input arguments" << std::endl;
	}
	else
	{
		std::ifstream inputFile(argv[1]);
		if (!inputFile) {
			std::cout << "Cannot find file, please check input filename" << std::endl;
		}
		else {
			bool readCorrectly;
			Handler* handleThis = new Handler();
			readCorrectly = *handleThis >> inputFile;
			inputFile.close();
			if (readCorrectly)
			{
				handleThis->executeProgram();
			}
		}
	}

}