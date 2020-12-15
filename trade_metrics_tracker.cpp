#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <exception>
#include <cmath>
#include "csvstream.h"

using namespace std;

class Trader {
public:
	string file;
private:
	Trader(string csvin)
		: file(csvin) { }
};