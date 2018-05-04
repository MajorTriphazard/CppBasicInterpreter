#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "LineNode.h"

using namespace std;

class ifStatement : public LineNode
{
public:
	ifStatement(string);
	~ifStatement();
};

