//header file for throwing exceptions 

#pragma once 

#include <string> 

using namespace std;

class invalidInput {
private:
	string msg;

public:
	invalidInput() {
		msg = "invalid input";
	}

	invalidInput(string m) {
		msg = "invalid input, " + m;
	}
	string what() {
		return msg;
	}
};
