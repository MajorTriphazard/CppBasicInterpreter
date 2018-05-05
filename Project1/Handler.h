#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <stack>
#include <map>
#include "LineNode.h"

//using namespace std;

class Handler {
public:
	std::map<std::string, int>* _variables;
	std::map<int, LineNode*>* _lineList;
	int _iterator;
	Handler();
	~Handler();
	bool operator>>(std::istream &input);
	bool executeProgram();
};