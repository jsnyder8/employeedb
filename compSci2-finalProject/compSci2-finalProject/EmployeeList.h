#pragma once
#include "employee.h"

#include <queue>
#include "sortAndSearch.h"

#include <iomanip>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

//defines for sort
#define byID 1
#define byLastName 2
#define byFirstName 3
#define bySSN 4
#define byAge 5
#define bySalary 6

#define USER_SEARCH 0
#define ADD_EMP_SEARCH 1
#define DELETE_EMP_SEARCH 2

#define ACSCENDING 1
#define DESCENDING 2

#define GREEN 10
#define WHITE 7

class EmployeeList :
	public employee
{
private:
	static string HEADERS[6];//used for headings, this will never change, only the order depending on the search

	int ids[100];
	string fNames[100];
	string lNames[100];
	string SSNs[100];
	int ages[100];
	double salaries[100];
	bool presentInDB[100];//mainly used for searches to double check a match is somebody in the db

	int posOfEmpOnSort[100];

	queue<int> posOfMatchedSearches;//used to hold the matches of a search, if there was no matches it should be an empty queue
	socialSecurity newEmpsSocial; //used to verify no employee has this social when adding a new employee
	socialSecurity deleteSocial; //used to verify that this employee does exist when deleting
	int length; //used to keep track of how big the array is

	int lastIndexSorted;//last field sorted (id, first, last, ssn, age, or salary)
	int lastOrderSorted;//acsending or descending
	static int countOfEmps;

public:
	~EmployeeList();//deletes the queue
	EmployeeList();//sets size = 0, 
	void addRecord(string, string, string, int, double); // used for the first 20 employees I add before the user
	void addRecord();//adds a record after verification the new employee is not already in our database, determined by a social search
	void deleteRecord();//deletes a record after verification this employee is in our database, determined by a social search
	void indexRecords(int, int acsOrDesc); //use the sortAndSearch Methods
	bool searchByField(int, int userOrComputerSearch);//if it is a user search it asks for value of field then searches
													  //if background search for add or delete the user is not prompted
	void display(); //displays the whole database in order of what field was last indexed
	void displaySearch();//displays the employees that matched the certain search
	void displayHeaders();//displays the top header section in order of what field was last indexed

	void deleteExistingFile();//used on startup
};

