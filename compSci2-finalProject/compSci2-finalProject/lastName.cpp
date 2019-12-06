#include "lastName.h"

lastName::lastName() {
	setLastName(" ");
}

lastName::lastName(string last) {
	setLastName(last);
}

void lastName::setLastName(string last) throw(invalidInput) {
	bool good = false;
	while (good == false) {
		try {
			if (last.length() > 20 || cin.fail()) {
				throw invalidInput("This is an invalid Last Name. Try again.");
			}
			else {
				strcpy_s(_lastName, last.c_str());
				good = true;
			}
		}
		catch (invalidInput error) {
			cout << error.what() << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Enter a Last Name: ";
			cin >> last;
		}
	}
}

char* lastName::getLastName() {
	return _lastName;
}

const lastName& lastName::operator=(const lastName& otherlastName) {
	if (this != &otherlastName) {
		setLastName(otherlastName._lastName);
	}
	return *this;
}
bool lastName::operator==(const lastName& otherlastName) {
	return strcmp(this->_lastName,  otherlastName._lastName) == 0;
}
bool lastName::operator!=(const lastName& otherlastName) {
	return strcmp(this->_lastName, otherlastName._lastName) != 0;
}

ostream& operator<<(ostream& outputStream, lastName& other) {
	string temp(other.getLastName());
	outputStream << temp;
	return outputStream;
}

istream& operator>>(istream& inputStream, lastName& other) {
	char tempLast[21];
	inputStream.getline(tempLast, 21);
	other.setLastName(tempLast);
	return inputStream;
}