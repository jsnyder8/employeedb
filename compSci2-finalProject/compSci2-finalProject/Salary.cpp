#include "Salary.h"
Salary::Salary() {
	setSalary(0);
}

Salary::Salary(double sal) {
	setSalary(sal);
}

void Salary::setSalary(double sal) throw (invalidInput) {
	bool good = false;
	while (good == false) {
		try {
			if (sal < 0 || cin.fail()) {
				throw invalidInput("This is an invalid Salary. Try again.");
			}
			else {
				salary = sal;
				good = true;
			}
		}
		catch (invalidInput error) {
			cout << error.what() << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Enter a Salary: ";
			cin >> sal;
		}
	}
}

double Salary::getSalary() {
	return salary;
}

const Salary& Salary::operator=(const Salary& otherSalary) {
	if (this != &otherSalary) {
		salary = otherSalary.salary;
	}
	return *this;
}
bool Salary::operator==(const Salary& otherSalary) {
	return this->salary == otherSalary.salary;
}
bool Salary::operator!=(const Salary& otherSalary) {
	return this->salary != otherSalary.salary;
}

ostream& operator<<(ostream& outputStream, Salary& other) {
	outputStream << other.salary;
	return outputStream;
}

istream& operator>>(istream& inputStream, Salary& other) {
	double temp;
	inputStream >> temp;
	other.setSalary(temp);
	return inputStream;
}