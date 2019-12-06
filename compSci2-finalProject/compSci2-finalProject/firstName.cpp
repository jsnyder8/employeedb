#include "firstName.h"

firstName::firstName() {
	setFirstName(" ");
}

firstName::firstName(string first) {
	setFirstName(first);
}

void firstName::setFirstName(string first) throw(invalidInput) {
	bool good = false;
	while (good == false) {
		try {
			if (first.length() > 20 || cin.fail()) {
				throw invalidInput("This is an invalid First Name. Try again.");
			}
			else {
				strcpy_s(_firstName, first.c_str());
				good = true;
			}
		}
		catch (invalidInput error) {
			cout << error.what() << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Enter a First Name: ";
			cin >> first;
		}
	}
}

char* firstName::getFirstName() {
	return _firstName;
}

const firstName& firstName::operator=(const firstName& otherfirstName) {
	if (this != &otherfirstName) {
		setFirstName(otherfirstName._firstName);
	}
	return *this;
}
bool firstName::operator==(const firstName& otherfirstName) {
	return strcmp(this->_firstName, otherfirstName._firstName) == 0;
}
bool firstName::operator!=(const firstName& otherfirstName) {
	return strcmp(this->_firstName, otherfirstName._firstName) != 0;
}

ostream& operator<<(ostream& outputStream, firstName& other) {
	string temp(other.getFirstName());
	outputStream << temp;
	return outputStream;
}

istream& operator>>(istream& inputStream, firstName& other) {
	char tempFirst[21];
	inputStream.getline(tempFirst, 21);
	other.setFirstName(tempFirst);
	return inputStream;
}