#include "sortAndSearch.h"
/*void sortAndSearch::swap(employee list[], int first, int second) {
	employee temp;
	temp = list[first];
	list[first] = list[second];
	list[second] = temp;
}

void sortAndSearch::recQuickSort(employee list[], int first, int last, int sortField) {
	int pivotLoc=0;

	if (first < last) {
		if (sortField == byID) {
			pivotLoc = partitionID(list, first, last);
		}
		else if (sortField == byFirstName || sortField == byLastName || sortField == bySSN) {
			pivotLoc = partitionStrings(list, first, last);
		}
		else if (sortField == byAge) {
			pivotLoc = partitionAge(list, first, last);
		}
		else if (sortField == bySalary) {
			pivotLoc = partitionSalary(list, first, last);
		}
		recQuickSort(list, first, pivotLoc - 1, sortField);
		recQuickSort(list, pivotLoc + 1, last, sortField);
	}
}

void sortAndSearch::quickSort(employee list[], int length, int sortField) {
	recQuickSort(list, 0, length, sortField);
}

int sortAndSearch::partitionID(employee list[], int first, int last) {
	ID pivot;
	int small = first;
	swap(list, first, (first + last) / 2);//swapping the type list

	pivot = list[first].getEmployeeID();
	int i;
	for (i = first + 1; i < last; i++); {
		if (list[i].getEmployeeID() <= pivot.getEmployeeID()) {
			small++;
			swap(list, small, i);
		}
	}

	swap(list, first, small);
	return small;
}

int sortAndSearch::partitionAge(employee list[], int first, int last) {
	Age pivot;
	int small = first;
	swap(list, first, (first + last) / 2);//swapping the type list

	pivot.setAge(list[first].getAge());
	int i = first + 1;

	for (int i = first + 1; i <= last; i++); {
		if (list[i].getAge() < pivot.getAge()) {
			small++;
			swap(list, small, i);
		}
	}

	swap(list, first, small);
	return small;
}

int sortAndSearch::partitionFirst(employee list[], int first, int last) {
	firstName pivot;
	int small = first;
	swap(list, first, (first + last) / 2);//swapping the type list

	pivot.setFirstName(list[first].getFirstName());

	int i = first + 1;

	for (int i = first + 1; i <= last; i++); {
		if ( strcmp( list[i].getFirstName(), pivot.getFirstName() ) < 0) {
			small++;
			swap(list, small, i);
		}
	}

	swap(list, first, small);
	return small;
}

int sortAndSearch::partitionLast(employee list[], int first, int last) {
	lastName pivot;
	int small = first;
	swap(list, first, (first + last) / 2);//swapping the type list

	pivot.setLastName(list[first].getLastName());

	int i = first + 1;

	for (int i = first + 1; i <= last; i++); {
		if (strcmp(list[i].getLastName(), pivot.getLastName()) < 0) {
			small++;
			swap(list, small, i);
		}
	}

	swap(list, first, small);
	return small;
}

int sortAndSearch::partitionSSN(employee list[], int first, int last) {
	socialSecurity pivot;
	int small = first;
	swap(list, first, (first + last) / 2);//swapping the type list
	small = first;

	pivot.setSocial(list[first].getSocial());

	int i = first + 1;

	for (int i = first + 1; i <= last; i++); {
		if (strcmp(list[i].getSocial(), pivot.getSocial()) < 0) {
			small++;
			swap(list, small, i);
		}
	}

	swap(list, first, small);
	return small;
}

int sortAndSearch::partitionSalary(employee list[], int first, int last) {
	Salary pivot;
	int small = first;
	swap(list, first, (first + last) / 2);//swapping the type list

	pivot.setSalary(list[first].getSalary());

	int i = first + 1;

	for (int i = first + 1; i <= last; i++); {
		if (list[i].getSalary() < pivot.getSalary()) {
			small++;
			swap(list, small, i);
		}
	}

	swap(list, first, small);
	return small;
}
*/