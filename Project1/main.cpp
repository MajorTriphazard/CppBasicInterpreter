#include "Handler.h"



int main() 
{
	
	Handler* handleThis = new Handler();
	ifstream myfile("C:\\Users\\Genna\\source\\repos\\Project1\\Project1\\Text.txt");
	*handleThis >> myfile;
	cin.get();
}