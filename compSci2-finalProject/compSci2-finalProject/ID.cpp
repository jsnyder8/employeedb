#include "ID.h"

ID::ID(){
	setEmployeeID(0);
}

ID::ID(int id) {
	setEmployeeID(id);
}

void ID::setEmployeeID(int numOfEmployees) {
	employeeID = numOfEmployees;
}

int ID::getEmployeeID() {
	return employeeID;
}

const ID& ID::operator=(const ID& otherID) {
	if (this != &otherID) {
		employeeID = otherID.employeeID;
	}
	return *this;
}
bool ID::operator==(const ID& otherID) {
	return this->employeeID == otherID.employeeID;
}
bool ID::operator!=(const ID& otherID) {
	return this->employeeID != otherID.employeeID;
}

ostream& operator<<(ostream& outputStream, ID& other) {
	outputStream << other.employeeID;
	return outputStream;
}

istream& operator>>(istream& inputStream, ID& other) {
	int temp;
	inputStream >> temp;
	other.employeeID = temp;
	return inputStream;
}