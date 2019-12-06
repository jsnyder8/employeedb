#pragma once
#include <iostream>
using namespace std;
class ID
{
private:
	int employeeID;

public:
	ID();
	ID(int id);

	const ID& operator=(const ID& otherID);
	bool operator==(const ID& otherID);
	bool operator!=(const ID& otherID);

	void setEmployeeID(int numOfEmployees);
	int getEmployeeID();

	friend ostream& operator<<(ostream& outputStream, ID& other);
	friend istream& operator>>(istream& inputStream, ID& other);
};

