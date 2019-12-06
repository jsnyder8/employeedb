#include "socialSecurity.h"

socialSecurity::socialSecurity() {
	setSocial("XXX-XX-XXXX");
}

socialSecurity::socialSecurity(string ssn) {
	setSocial(ssn);
}

char* socialSecurity::getSocial() {
	return social;
}

void socialSecurity::setSocial(string ssn) throw (invalidInput) {
	strcpy_s(social, ssn.c_str());
	/*
	bool good = false;
	while (good == false) {
		try {
			if(ssn.length() == 11){
				if ((ssn[3] != '-' && ssn[6] != '-') || cin.fail()) {
					throw invalidInput("This is an invalid Social, you need to include '-' to seperate the parts. Try again.");
					cout << ssn.length() << endl;
					cout << ssn[3] << endl << ssn[6] << endl;
				}
			}
			else {
				strcpy_s(social, ssn.c_str());
				cout << "good copy" << endl;
				good = true;
			}
		}
		catch (invalidInput error) {
			cout << error.what() << endl;
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Enter a Social in the form XXX-XX-XXXX : ";
			cin >> ssn;
		}
	}
	*/
}

const socialSecurity& socialSecurity::operator=(const socialSecurity& otherSocial) {
	if (this != &otherSocial) {
		setSocial(otherSocial.social);
	}
	return *this;
}
bool socialSecurity::operator==(const socialSecurity& otherSocial) {
	return strcmp(this->social, otherSocial.social) == 0;
}
bool socialSecurity::operator!=(const socialSecurity& otherSocial) {
	return strcmp(this->social, otherSocial.social) != 0;
}

ostream& operator<<(ostream& outputStream, socialSecurity& other) {
	string temp(other.getSocial());
	outputStream << temp;
	return outputStream;
}

istream& operator>>(istream& inputStream, socialSecurity& other) {
	char tempArray[12];
	inputStream.getline(tempArray, 12);
	other.setSocial(tempArray);
	return inputStream;
}