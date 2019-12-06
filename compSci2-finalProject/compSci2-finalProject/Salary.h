#pragma once
#include <iostream>
#include "invalidInput.h"
using namespace std;
class Salary
{
private:
	double salary;

public:
	Salary();
	Salary(double sal);

	const Salary& operator=(const Salary& otherSalary);
	bool operator==(const Salary& otherSalary);
	bool operator!=(const Salary& otherSalary);

	void setSalary(double sal) throw (invalidInput);
	double getSalary();

	friend ostream& operator<<(ostream& outputStream, Salary& other);
	friend istream& operator>>(istream& inputStream, Salary& other);
};

