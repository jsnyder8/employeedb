#pragma once
#include <string>
#include <iostream>
#include "invalidInput.h"
using namespace std;
class lastName
{
private:
	char _lastName[21];

public:
	lastName();
	lastName(string last);

	const lastName& operator=(const lastName& otherlastName);
	bool operator==(const lastName& otherlastName);
	bool operator!=(const lastName& otherlastName);

	char* getLastName();
	void setLastName(string last) throw (invalidInput);

	friend ostream& operator<<(ostream& outputStream, lastName& other);
	friend istream& operator>>(istream& inputStream, lastName& other);
};

