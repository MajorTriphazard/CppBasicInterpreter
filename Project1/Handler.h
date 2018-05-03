#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;

class Handler {
public:
	map<char, int>* variables;
	int lineItterator;

	Handler();
	~Handler();
	bool operator>>(istream &input);
};