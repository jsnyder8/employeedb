//employee.cpp 
#include "employee.h" 


bool employee::operator==(const employee& otherEmp) {
	return (employeeID == otherEmp.employeeID && empLastName == otherEmp.empLastName && empFirstName == otherEmp.empFirstName && social == otherEmp.social && salary == otherEmp.salary && age == otherEmp.age);
}

bool employee::operator!=(const employee& otherEmp) {
	return (employeeID != otherEmp.employeeID || empLastName != otherEmp.empLastName || empFirstName != otherEmp.empFirstName || social != otherEmp.social || salary != otherEmp.salary || age != otherEmp.age);
}

const employee& employee::operator=(const employee& otherEmp) {
	if (this != &otherEmp) {
		employeeID = otherEmp.employeeID;
		empFirstName = otherEmp.empFirstName;
		empLastName = otherEmp.empLastName;
		social = otherEmp.social;
		salary = otherEmp.salary;
		age = otherEmp.age;
		isOccupied = otherEmp.isOccupied;
	}
	return *this;
}

employee::employee(const employee& otherEmp) {
	employeeID = otherEmp.employeeID;
	empFirstName = otherEmp.empFirstName;
	empLastName = otherEmp.empLastName;
	social = otherEmp.social;
	salary = otherEmp.salary;
	age = otherEmp.age;
	isOccupied = otherEmp.isOccupied;
}

employee::employee() {
	setEmployeeID(0);
	setLastName(" ");
	setFirstName(" ");
	setSocial("XXX-XX-XXXX");
	setSalary(0);
	setAge(0);
	setIsOccupied(true);
}

employee::employee(string first, string last, string ssn, int a, double sal) {
	setLastName(last);
	setFirstName(first);
	setSocial(ssn);
	setSalary(sal);
	setAge(a);
	setIsOccupied(true);
}

void employee::readInfo() throw (invalidInput) {
	string temp;
	//try catch around the inputs needed at some point
	cout << "Enter last name: ";
	cin >> temp;
	empLastName.setLastName(temp);

	cout << "Enter first name: ";
	cin >> temp;
	empFirstName.setFirstName(temp);

	cout << "Enter salary: ";
	cin >> salary;

	cout << "Enter age: ";
	cin >> age;

	/*

	while (!good) {
		try {
			if (strlen(firstName) > 20 || strlen(lastName) > 20)
				throw invalidInput("the name is too long. First and last names should be a max of 20 characters");
			else if (strlen(social) != 11)
				throw invalidInput("social security # must be in 'XXX-XX-XXXX' format");
			good = true;
		}catch (invalidInput name) {
			cout << name.what() << endl;
			cin.clear();
		}
		catch (invalidInput soc) {
			cout << soc.what() << endl;
			cin.clear();
		}
	}
	*/
}



int employee::getEmployeeID() {
	return employeeID.getEmployeeID();
}

char* employee::getLastName() {
	return empLastName.getLastName();
}

char* employee::getFirstName() {
	return empFirstName.getFirstName();
}

char* employee::getSocial() {
	return social.getSocial();
}

double employee::getSalary() {
	return salary.getSalary();
}

int employee::getAge() {
	return age.getAge();
}

bool employee::getIsOccupied() {
	return isOccupied;
}

void employee::setIsOccupied(bool is) {
	isOccupied = is;
}

void employee::setEmployeeID(int id) {
	employeeID.setEmployeeID(id);
}

void employee::setLastName(string last){
	empLastName.setLastName(last);
}

void employee::setFirstName(string first){
	empFirstName.setFirstName(first);
}

void employee::setSocial(string ssn){
	social.setSocial(ssn);
}

void employee::setSalary(double sal){
	salary.setSalary(sal);
}

void employee::setAge(int a){
	age.setAge(a);
}

/* 
void employee::printRecord() {

	cout << fixed << showpoint << setprecision(2);

	cout << setw(10) << "employee ID" << setw(20) << "last Name" << setw(20) << "first Name"
		<< setw(15) << "social" << setw(10) << "salary" << setw(6) << "age" << endl;

	cout << setw(10) << employeeID << setw(20) << lastName << setw(20) << firstName
		<< setw(15) << social << setw(10) << salary << setw(6) << age << endl;
}
*/