#pragma once
#include <string>
#include <iostream>
#include "invalidInput.h"
using namespace std;
class firstName
{
private:
	char _firstName[21];

public:
	firstName();
	firstName(string first);

	const firstName& operator=(const firstName& otherfirstName);
	bool operator==(const firstName& otherfirstName);
	bool operator!=(const firstName& otherfirstName);

	char* getFirstName();
	void setFirstName(string first) throw(invalidInput);

	friend ostream& operator<<(ostream& outputStream, firstName& other);
	friend istream& operator>>(istream& inputStream, firstName& other);
};

