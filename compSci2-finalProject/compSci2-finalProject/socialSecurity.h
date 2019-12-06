#pragma once
#include <string>
#include <iostream>
#include "invalidInput.h"
using namespace std;
class socialSecurity
{
private:
	char social[12];

public:
	socialSecurity();
	socialSecurity(string ssn);

	const socialSecurity& operator=(const socialSecurity& otherSocial);
	bool operator==(const socialSecurity& otherSocial);
	bool operator!=(const socialSecurity& otherSocial);

	char* getSocial();
	void setSocial(string ssn) throw (invalidInput);

	friend ostream& operator<<(ostream& outputStream, socialSecurity& other);
	friend istream& operator>>(istream& inputStream, socialSecurity& other);
};

