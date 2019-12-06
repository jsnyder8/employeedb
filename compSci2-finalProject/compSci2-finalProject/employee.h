//employee.h file 
#pragma once 

#include "ID.h"
#include "firstName.h"
#include "lastName.h"
#include "socialSecurity.h"
#include "Age.h"
#include "Salary.h"

#include <iostream> 
#include <cstring> 
#include <iomanip> 

using namespace std;

class employee
{
protected:
	ID employeeID;
	lastName empLastName;
	firstName empFirstName;
	socialSecurity social;
	Age age;
	Salary salary;
	bool isOccupied;

public:
	//operator overload 
	const employee& operator=(const employee& otherEmp);
	bool operator==(const employee& otherEmp);
	bool operator!=(const employee& otherEmp);

	employee(const employee& otherEmp);
	employee(string first, string last, string ssn, int a, double sal);
	employee();
	void readInfo();

	int getEmployeeID();
	char* getLastName();
	char* getFirstName();
	char* getSocial();
	double getSalary();
	int getAge();
	bool getIsOccupied();

	void setEmployeeID(int id);
	void setLastName(string last);
	void setFirstName(string first);
	void setSocial(string ssn);
	void setSalary(double);
	void setAge(int);
	void setIsOccupied(bool);

	//void printRecord();
};

