#pragma once
#include <iostream>
#include "invalidInput.h"
using namespace std;
class Age
{
private:
	int age;

public:
	Age();
	Age(int);

	const Age& operator=(const Age& otherAge);
	bool operator==(const Age& otherAge);
	bool operator!=(const Age& otherAge);

	void setAge(int) throw (invalidInput);
	int getAge();

	friend ostream& operator<<(ostream& outputStream, Age& other);
	friend istream& operator>>(istream& inputStream, Age& other);
};

