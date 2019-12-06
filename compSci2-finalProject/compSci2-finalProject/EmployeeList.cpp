#include "EmployeeList.h"

int EmployeeList::countOfEmps = 1;

//sets the db defaults
EmployeeList::EmployeeList() {
	length = 0;
	lastIndexSorted = byID;
	lastOrderSorted = ACSCENDING;
}

//takes care of the queue memory management
EmployeeList::~EmployeeList() {
	posOfMatchedSearches.~queue();
}

//used on startup
void EmployeeList::deleteExistingFile() {
	remove("employeeRecords.dat");
}


//***********THIS IS THE INTIAL 20 EMPLOYEES ADD**********
//takes parameters and sets them equal to an employee object
//adds that employee into the records
void EmployeeList::addRecord(string first, string last, string ssn, int a, double sal) {
	int tempLastSort = lastIndexSorted;
	int tempLastOrder = lastOrderSorted;

	employee newEmp(first, last, ssn, a, sal);
	newEmp.setEmployeeID(countOfEmps);
	countOfEmps++;

	ofstream outFile;
	outFile.open("employeeRecords.dat", ios::binary | ios::app);
	if (!outFile) {
		cout << "cant open employeeRecords.dat" << endl;
	}

	outFile.seekp(0, ios::end);//puts the writing position at the end
	outFile.write((char*)& newEmp, sizeof(newEmp));
	outFile.close();
	if (outFile.good() == false) {
		cout << "Error occured while writing in new employee" << endl;
	}

	lastIndexSorted = bySSN;
	
	displayHeaders();
	cout << left << setw(17) << newEmp.getSocial()
		<< setw(10) << newEmp.getEmployeeID() 
		<< setw(20) << newEmp.getLastName() 
		<< setw(20) << newEmp.getFirstName() 
		<< setw(10) << newEmp.getAge() 
		<< setw(20) << setprecision(2)<< newEmp.getSalary() << endl;
	
	cout << "New employee record added to file successfully. " << endl;

	indexRecords(tempLastSort, tempLastOrder);
}

//***********THIS IS THE USER ADD***********************
//asks for a social to add
//searches for that social
//if social isnt found, it asks for the rest of that persons credentials and adds them to the records
//if social is found, lets the user know that person is already in the db
void EmployeeList::addRecord() {
	int tempLastSort = lastIndexSorted;
	int tempLastOrder = lastOrderSorted;

	string temp;
	cout << "Enter the new employee's social: ";
	cin >> temp;
	newEmpsSocial.setSocial(temp);

	
	//if not found then go through process of getting more info and adding the new emp
	if (searchByField(bySSN, ADD_EMP_SEARCH) == false) {
		fstream outFile;
		outFile.open("employeeRecords.dat", ios::binary | ios::app | ios::in);
		if (!outFile) {
			cout << "cant open employeeRecords.dat" << endl;
		}

		//creating new employee and getting his/her credentials
		employee newEmp;
		newEmp.readInfo();
		newEmp.setSocial(newEmpsSocial.getSocial());
		newEmp.setEmployeeID(countOfEmps);
		countOfEmps++;

		outFile.seekp(0, ios::end);//puts the writing position at the end
		outFile.write((char*)& newEmp, sizeof(newEmp));
		outFile.close();
		if (outFile.good() == false) {
			cout << "Error occured while writing in new employee" << endl;
		}

		cout << fixed << left;
		displayHeaders();
		cout << left << setw(17) << newEmp.getSocial()
			<< setw(10) << newEmp.getEmployeeID() 
			<< setw(20) << newEmp.getLastName() 
			<< setw(20) << newEmp.getFirstName() 
			<< setw(10) << newEmp.getAge() 
			<< setw(10) << setprecision(2) << newEmp.getSalary() << endl;
		cout << "New employee record added to file successfully. " << endl;
	}
	else {
		///////////////////////////////////////////
		//IF THIS EMPLOYEE ALREADY EXISTS
		//////////////////////////////////////////
		displaySearch();
		cout << "This employee already exists in our Database." << endl;
	}

	indexRecords(tempLastSort, tempLastOrder);
}

//asks for a social to delete
//searches for that social
//if social is found, it goes in and switches that employees attribute isOccupied = false
//rewrites that emp into the records with the update
//if social not found, lets the user know that person doesnt exist
void EmployeeList::deleteRecord() {
	int tempLastSort = lastIndexSorted;
	int tempLastOrder = lastOrderSorted;

	string temp;
	cout << "Enter the Social of the employee record you wish to delete: ";
	cin >> temp;
	deleteSocial.setSocial(temp);

	employee deletedEmp;

	if (searchByField(bySSN, DELETE_EMP_SEARCH) == true) {
		//opening files and making sure they were correctly opened
		fstream file;
		file.open("employeeRecords.dat", ios::binary | ios::out | ios::in);

		if (!file) {
			cout << "cant open employeeRecords.dat" << endl;
		}
		else {
			//used to go through the binary file
			bool found = false;
			employee dummyEmp; 
			employee deletedEmp;
			int pos = 0;
			file.seekg(0, ios::beg);
			file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
			pos++;
			while (!found) {
				//if the current social doesnt equal the social to be deleted
				if (strcmp(deleteSocial.getSocial(), dummyEmp.getSocial()) == 0) {
					dummyEmp.setIsOccupied(false);
					deletedEmp = dummyEmp;
					file.seekp(pos * sizeof(dummyEmp), ios::beg);
					file.write((char*)& dummyEmp, sizeof(dummyEmp));//writing record in
					found = true;
				}
				pos++;
				file.seekg(pos * sizeof(dummyEmp), ios::beg);
				file.read((char*)& dummyEmp, sizeof(dummyEmp));//loop control variable
			}

			file.close();
			if (!file.good()) {
				cout << "Problem occurred while deleting employee." << endl;
			}
			//for the user, telling them the employee was deleted
			displayHeaders();
			cout << left << setw(17) << deletedEmp.getSocial()
				<< setw(10) << deletedEmp.getEmployeeID()
				<< setw(20) << deletedEmp.getLastName()
				<< setw(20) << deletedEmp.getFirstName()
				<< setw(10) << deletedEmp.getAge()
				<< setw(10) << setprecision(2) << deletedEmp.getSalary() << endl;
			cout << "This employee has been deleted successfully." << endl;
		}
	}
	else {
		//this is if the employee wasnt found in the database
		cout << "The employee by the social of " << deleteSocial.getSocial() << " was not in our database to begin with." << endl;
	}

	indexRecords(tempLastSort, tempLastOrder);
}

//takes in what field to search and if it is acsending or descending
//performs a heap sort on that field
void EmployeeList::indexRecords(int sortBy, int acsOrdesc) {
	ifstream file;
	file.open("employeeRecords.dat", ios::binary | ios::in);
	if (!file) {
		cout << "cant open employeeRecords.dat" << endl;
	}
	file.seekg(0, ios::beg);
	//local variables
	employee dummyEmp;
	int i = 0;//to later be set as length
	sortAndSearch<int> intSorter;
	sortAndSearch<string> stringSorter;
	sortAndSearch<double> doubleSorter;

	if (sortBy == byID) {
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
		while (!file.eof()) {
			posOfEmpOnSort[i] = i;
			ids[i] = dummyEmp.getEmployeeID();
			presentInDB[i] = dummyEmp.getIsOccupied();
			i++;
			file.read((char*)& dummyEmp, sizeof(dummyEmp));//loop control variable
		}

		length = i;

		intSorter.heapSort(posOfEmpOnSort, ids, presentInDB, length);

		if (acsOrdesc == DESCENDING) {
			intSorter.reverseOrder(posOfEmpOnSort, ids, presentInDB, 0,  length - 1);
		}
	}
	else if (sortBy == byFirstName) {
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
		while (!file.eof()) {
			posOfEmpOnSort[i] = i;
			fNames[i] = dummyEmp.getFirstName();
			presentInDB[i] = dummyEmp.getIsOccupied();
			i++;
			file.read((char*)& dummyEmp, sizeof(dummyEmp));//loop control variable
		}

		length = i;

		stringSorter.heapSort(posOfEmpOnSort, fNames, presentInDB, length);

		if (acsOrdesc == DESCENDING) {
			stringSorter.reverseOrder(posOfEmpOnSort, fNames, presentInDB, 0, length - 1);
		}
	}
	else if (sortBy == byLastName) {
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
		while (!file.eof()) {
			posOfEmpOnSort[i] = i;
			lNames[i] = dummyEmp.getLastName();
			presentInDB[i] = dummyEmp.getIsOccupied();
			i++;
			file.read((char*)& dummyEmp, sizeof(dummyEmp));//loop control variable
		}

		length = i;

		stringSorter.heapSort(posOfEmpOnSort, lNames, presentInDB, length);

		if (acsOrdesc == DESCENDING) {
			stringSorter.reverseOrder(posOfEmpOnSort, lNames, presentInDB, 0, length - 1);
		}
	}
	else if (sortBy == bySSN) {
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
		while (!file.eof()) {
			posOfEmpOnSort[i] = i;
			SSNs[i] = dummyEmp.getSocial();
			presentInDB[i] = dummyEmp.getIsOccupied();
			i++;
			file.read((char*)& dummyEmp, sizeof(dummyEmp));//loop control variable
		}

		length = i;

		stringSorter.heapSort(posOfEmpOnSort, SSNs, presentInDB, length);

		if (acsOrdesc == DESCENDING) {
			stringSorter.reverseOrder(posOfEmpOnSort, SSNs, presentInDB, 0, length - 1);
		}
	}
	else if (sortBy == byAge) {
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
		while (!file.eof()) {
			posOfEmpOnSort[i] = i;
			ages[i] = dummyEmp.getAge();
			presentInDB[i] = dummyEmp.getIsOccupied();
			i++;
			file.read((char*)& dummyEmp, sizeof(dummyEmp));//loop control variable
		}

		length = i;

		intSorter.heapSort(posOfEmpOnSort, ages, presentInDB, length);

		if (acsOrdesc == DESCENDING) {
			intSorter.reverseOrder(posOfEmpOnSort, ages, presentInDB, 0, length - 1);
		}
	}
	else if (sortBy == bySalary) {
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
		while (!file.eof()) {
			posOfEmpOnSort[i] = i;
			salaries[i] = dummyEmp.getSalary();
			presentInDB[i] = dummyEmp.getIsOccupied();
			i++;
			file.read((char*)& dummyEmp, sizeof(dummyEmp));//loop control variable
		}

		length = i;

		doubleSorter.heapSort(posOfEmpOnSort, salaries, presentInDB, length);

		if (acsOrdesc == DESCENDING) {
			doubleSorter.reverseOrder(posOfEmpOnSort, salaries, presentInDB, 0, length - 1);
		}
	}
	file.close();
	
	lastIndexSorted = sortBy;
	lastOrderSorted = acsOrdesc;
}

//takes parameters of what field to be searched and if it is a user search, or if the program is searching for the add/delete function
//sorts the data by the search field
//if user search it prompts for the user to enter what the want to search for
//if computer(only for a social search), sets the search Item equal to the social of the emp to be added/deleted
//Social and ID searches should only return 1 value
//Other fields will return a range with all those that match the search criteria
//returns true if an emp was found or false if no emp was found
bool EmployeeList::searchByField(int searchBy, int useForSearch) {
	while (posOfMatchedSearches.empty() == false) {
		posOfMatchedSearches.pop();
	}

	int resultHigher = 0;
	int resultLower = 0;
	indexRecords(searchBy, ACSCENDING);

	sortAndSearch<int> intSorter;
	sortAndSearch<string> stringSorter;
	sortAndSearch<double> doubleSorter;

	if (searchBy == bySSN) {
		socialSecurity searchSocial;
		if(useForSearch == ADD_EMP_SEARCH){
			searchSocial = newEmpsSocial;
		}
		else if (useForSearch == DELETE_EMP_SEARCH) {
			searchSocial.setSocial(deleteSocial.getSocial());
		}
		else {
			string temp;
			cout<<"Enter a SSN to search for: ";
			cin>> temp;
			searchSocial.setSocial(temp);
		}
		
		resultHigher = stringSorter.binarySearch(SSNs, presentInDB, 0, length, searchSocial.getSocial());
		//this should be if bc there should only be 1 of each social
		if (resultHigher != -1) {
			posOfMatchedSearches.push(posOfEmpOnSort[resultHigher]);
		}
	}
	else if (searchBy == byID) {
		ID searchID;
		cout << "Enter an ID to search for: ";
		cin >> searchID;

		resultHigher = intSorter.binarySearch(ids, presentInDB, 0, length, searchID.getEmployeeID());
		//this should be if bc there should only be 1 of each social
		if (resultHigher != -1) {
			posOfMatchedSearches.push(posOfEmpOnSort[resultHigher]);
		}
	}
	else if (searchBy == byAge) {
		Age searchAge;

		cout << "Enter an Age to search for: ";
		cin >> searchAge;
		//while makes sure all people with that First are included
		resultLower = intSorter.firstOccurrence(ages, presentInDB, 0, length - 1, searchAge.getAge(), length);
		resultHigher = intSorter.lastOccurrence(ages, presentInDB, 0, length-1, searchAge.getAge(), length);
		if (resultHigher != -1 && resultLower != -1) {
			for (int j = resultLower; j <= resultHigher; j++) {
				posOfMatchedSearches.push(posOfEmpOnSort[j]);
			}
		}
	}
	else if (searchBy == bySalary) {
		Salary searchSalary;

		cout << "Enter an Salary to search for: ";
		cin >> searchSalary;

		//while makes sure all people with that Salary are included
		resultLower = doubleSorter.firstOccurrence(salaries, presentInDB, 0, length - 1, searchSalary.getSalary(), length);
		resultHigher = doubleSorter.lastOccurrence(salaries, presentInDB, 0, length - 1, searchSalary.getSalary(), length);
		if (resultHigher != -1 && resultLower != -1) {
			for (int j = resultLower; j <= resultHigher; j++) {
				posOfMatchedSearches.push(posOfEmpOnSort[j]);
			}
		}
	}
	else if (searchBy == byFirstName) {
		string temp;
		firstName searchFirst;
		cout << "Enter an First to search for: ";
		cin >> temp;
		searchFirst.setFirstName(temp);
		//while makes sure all people with that First are included
		resultLower = stringSorter.firstOccurrence(fNames, presentInDB, 0, length - 1, searchFirst.getFirstName(), length);
		resultHigher = stringSorter.lastOccurrence(fNames, presentInDB, 0, length - 1, searchFirst.getFirstName(), length);
		if (resultHigher != -1 && resultLower != -1) {
			for (int j = resultLower; j <= resultHigher; j++) {
				posOfMatchedSearches.push(posOfEmpOnSort[j]);
			}
		}
	}
	else if (searchBy == byLastName) {
		lastName searchLast;
		string temp;
		cout << "Enter a Last to search for: ";
		cin >> temp;
		searchLast.setLastName(temp);

		//while makes sure all people with that First are included
		resultLower = stringSorter.firstOccurrence(lNames, presentInDB, 0, length - 1, searchLast.getLastName(), length);
		resultHigher = stringSorter.lastOccurrence(lNames, presentInDB, 0, length - 1, searchLast.getLastName(), length);
		if (resultHigher != -1 && resultLower != -1) {
			for (int j = resultLower; j <= resultHigher; j++) {
				posOfMatchedSearches.push(posOfEmpOnSort[j]);
			}
		}
	}

	if (posOfMatchedSearches.empty() == true) {
		return false;
	}
	else {
		return true;
	}
	
}

string EmployeeList::HEADERS[6] = { "EMP ID", "LAST NAME", "FIRST NAME", "SSN", "AGE", "SALARY" };

//displays the header fields in order of last sort
void EmployeeList::displayHeaders() {
	system("CLS");

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, GREEN);

	cout << fixed << right;
	if (lastIndexSorted == byID) {
		cout <<left << setw(10) << HEADERS[0] 
			<<setw(20)<< HEADERS[1] 
			<< setw(20) << HEADERS[2] 
			<< setw(20) << HEADERS[3] 
			<< setw(10) << HEADERS[4] 
			<< setw(20) << HEADERS[5] <<endl;
	}
	else if (lastIndexSorted == bySSN) {
		cout <<left<<setw(17)<<HEADERS[3] 
			<< setw(10) << HEADERS[0] 
			<< setw(20) << HEADERS[1] 
			<< setw(20) << HEADERS[2] 
			<< setw(10) << HEADERS[4] 
			<< setw(20) << HEADERS[5] << endl;
	}
	else if (lastIndexSorted == byLastName) {
		cout <<left<<setw(20)<< HEADERS[1] 
			<< setw(20) << HEADERS[2]
			<< setw(10) << HEADERS[0] 
			<< setw(20) << HEADERS[3] 
			<< setw(10) << HEADERS[4] 
			<< setw(20) << HEADERS[5] << endl;
	}
	else if (lastIndexSorted == byFirstName) {
		cout << left << setw(20) << HEADERS[2]
			<< setw(20) << HEADERS[1] 
			<< setw(10) << HEADERS[0] 
			<< setw(20) << HEADERS[3] 
			<< setw(10) << HEADERS[4] 
			<< setw(20) << HEADERS[5] << endl;
	}
	else if (lastIndexSorted == byAge) {
		cout << left << setw(10) << HEADERS[4]
			<< setw(10) << HEADERS[0] 
			<< setw(20) << HEADERS[1] 
			<< setw(20) << HEADERS[2] 
			<< setw(20) << HEADERS[3] 
			<< setw(20) << HEADERS[5] << endl;
	}
	else if (lastIndexSorted == bySalary) {
		cout << left << setw(15) << setprecision(2) << HEADERS[5]
			<< setw(10) << HEADERS[0] 
			<< setw(20) << HEADERS[1] 
			<< setw(20) << HEADERS[2] 
			<< setw(20) << HEADERS[3] 
			<< setw(5) << HEADERS[4] << endl;
	}
	SetConsoleTextAttribute(hConsole, WHITE);
}

//opens record file
//uses the position of sort array to seek and read in emps in order of sorted field
//checks to make sure the emp is in the array
//prints out the emp
void EmployeeList::display() {
	displayHeaders();
	cout << fixed << right;

	ifstream file;
	file.open("employeeRecords.dat", ios::binary | ios::in);
	if (!file) {
		cout << "cant open employeeRecords.dat" << endl;
	}

	//local variables
	employee dummyEmp;
	file.seekg(0, ios::beg);

	for (int i = 0; i < length; i++) {
		file.seekg(sizeof(dummyEmp)*posOfEmpOnSort[i], ios::beg);//seek to the position of the employee to be printed
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read in employee
		if (dummyEmp.getIsOccupied() == true) {
			if (lastIndexSorted == byID) {
				cout << left << setw(10) << dummyEmp.getEmployeeID()
					<< setw(20) << dummyEmp.getLastName()
					<< setw(20) << dummyEmp.getFirstName()
					<< setw(20) << dummyEmp.getSocial()
					<< setw(10) << dummyEmp.getAge()
					<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
			}
			else if (lastIndexSorted == bySSN) {
				cout << left << setw(17) << dummyEmp.getSocial()
					<< setw(10) << dummyEmp.getEmployeeID()
					<< setw(20) << dummyEmp.getLastName()
					<< setw(20) << dummyEmp.getFirstName()
					<< setw(10) << dummyEmp.getAge()
					<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
			}
			else if (lastIndexSorted == byLastName) {
				cout << left << setw(20) << dummyEmp.getLastName()
					<< setw(20) << dummyEmp.getFirstName()
					<< setw(10) << dummyEmp.getEmployeeID()
					<< setw(20) << dummyEmp.getSocial()
					<< setw(10) << dummyEmp.getAge()
					<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
			}
			else if (lastIndexSorted == byFirstName) {
				cout << left << setw(20) << dummyEmp.getFirstName()
					<< setw(20) << dummyEmp.getLastName()
					<< setw(10) << dummyEmp.getEmployeeID()
					<< setw(20) << dummyEmp.getSocial()
					<< setw(10) << dummyEmp.getAge()
					<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
			}
			else if (lastIndexSorted == byAge) {
				cout << left << setw(10) << dummyEmp.getAge()
					<< setw(10) << dummyEmp.getEmployeeID()
					<< setw(20) << dummyEmp.getLastName()
					<< setw(20) << dummyEmp.getFirstName()
					<< setw(20) << dummyEmp.getSocial()
					<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
			}
			else if (lastIndexSorted == bySalary) {
				cout << left << setw(15) << setprecision(2) << dummyEmp.getSalary()
					<< setw(10) << dummyEmp.getEmployeeID()
					<< setw(20) << dummyEmp.getLastName()
					<< setw(20) << dummyEmp.getFirstName()
					<< setw(20) << dummyEmp.getSocial()
					<< setw(10) << dummyEmp.getAge() << endl;
			}
		}
		
	}	
	file.close();
}

//opens record file
//uses the queue of matched searches to find emp in records until it is empty
//checks to make sure the emp is in the array
//prints out the searched emp
void EmployeeList::displaySearch() {
	displayHeaders();
	cout << fixed << right;

	ifstream file;
	file.open("employeeRecords.dat", ios::binary | ios::in);
	if (!file) {
		cout << "cant open employeeRecords.dat" << endl;
	}

	//local variables
	employee dummyEmp;
	file.seekg(0, ios::beg);

	while (posOfMatchedSearches.empty() == false) {
		file.seekg(sizeof(dummyEmp) * posOfMatchedSearches.front(), ios::beg);//seek to the emp found
		file.read((char*)& dummyEmp, sizeof(dummyEmp));//read first employee from file
		
		if (dummyEmp.getIsOccupied() == true) {
				if (lastIndexSorted == byID) {
					cout << left << setw(10) << dummyEmp.getEmployeeID()
						<< setw(20) << dummyEmp.getLastName()
						<< setw(20) << dummyEmp.getFirstName()
						<< setw(20) << dummyEmp.getSocial()
						<< setw(10) << dummyEmp.getAge()
						<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
				}
				else if (lastIndexSorted == bySSN) {
					cout << left << setw(17) << dummyEmp.getSocial()
						<< setw(10) << dummyEmp.getEmployeeID()
						<< setw(20) << dummyEmp.getLastName()
						<< setw(20) << dummyEmp.getFirstName()
						<< setw(10) << dummyEmp.getAge()
						<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
				}
				else if (lastIndexSorted == byLastName) {
					cout << left << setw(20) << dummyEmp.getLastName()
						<< setw(20) << dummyEmp.getFirstName()
						<< setw(10) << dummyEmp.getEmployeeID()
						<< setw(20) << dummyEmp.getSocial()
						<< setw(10) << dummyEmp.getAge()
						<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
				}
				else if (lastIndexSorted == byFirstName) {
					cout << left << setw(20) << dummyEmp.getFirstName()
						<< setw(20) << dummyEmp.getLastName()
						<< setw(10) << dummyEmp.getEmployeeID()
						<< setw(20) << dummyEmp.getSocial()
						<< setw(10) << dummyEmp.getAge()
						<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
				}
				else if (lastIndexSorted == byAge) {
					cout << left << setw(10) << dummyEmp.getAge()
						<< setw(10) << dummyEmp.getEmployeeID()
						<< setw(20) << dummyEmp.getLastName()
						<< setw(20) << dummyEmp.getFirstName()
						<< setw(20) << dummyEmp.getSocial()
						<< setw(20) << setprecision(2) << dummyEmp.getSalary() << endl;
				}
				else if (lastIndexSorted == bySalary) {
					cout << left << setw(15) << setprecision(2) << dummyEmp.getSalary()
						<< setw(10) << dummyEmp.getEmployeeID()
						<< setw(20) << dummyEmp.getLastName()
						<< setw(20) << dummyEmp.getFirstName()
						<< setw(20) << dummyEmp.getSocial()
						<< setw(10) << dummyEmp.getAge() << endl;
				}
		}
		posOfMatchedSearches.pop();
	}
	file.close();
}
