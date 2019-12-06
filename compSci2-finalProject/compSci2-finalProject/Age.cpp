#include "Age.h"

Age::Age() {
	setAge(0);
}

Age::Age(int a) {
	setAge(a);
}

void Age::setAge(int a) throw (invalidInput) {
	bool good = false;
	while (good == false) {
		try {
			if (a < 0 || cin.fail()) {
				throw invalidInput("This is an invalid Age. Try again.");
			}
			else {
				age = a;
				good = true;
			}
		}
		catch (invalidInput error) {
			cout << error.what() << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Enter an Age: ";
			cin >> a;
		}		
	}
}

int Age::getAge() {
	return age;
}

const Age& Age::operator=(const Age& otherAge) {
	if (this != &otherAge) {
		age = otherAge.age;
	}
	return *this;
}
bool Age::operator==(const Age& otherAge) {
	return this->age == otherAge.age;
}
bool Age::operator!=(const Age& otherAge) {
	return this->age != otherAge.age;
}

ostream& operator<<(ostream& outputStream, Age& other) {
	outputStream << other.age;
	return outputStream;
}

istream& operator>>(istream& inputStream, Age& other) {
	int temp;
	inputStream >> temp;
	other.setAge(temp);
	return inputStream;
}