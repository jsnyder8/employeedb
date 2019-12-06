//header file for searching and sorting algorithms 

#pragma once 
#include <iostream>
using namespace std;
//SORTING ALGORITHMS ARE OUT OF WACK

template <class Type>
class sortAndSearch {
private:
	void heapify(int ids[], Type list[], bool present[], int n, int i);
	void Swap(int ids[], Type list[], bool present[], int first, int second);//swaps array if first position with second
public:	
	void reverseOrder(int ids[], Type list[], bool present[], int start, int end);//used on descending order sort
	void heapSort(int ids[], Type list[], bool present[], int n);
	int binarySearch(Type list[], bool present[], int first, int length, Type searchItem);//used for id and social search

	//these two are used for any other search, because there can be multiple of the same search criteria
	int firstOccurrence(Type list[], bool present[], int low, int high, Type searchItem, int n);//finds the first occurrence
	int lastOccurrence(Type list[], bool present[], int low, int high, Type searchItem, int n);//finds the last occurrence
};

template <class Type>
int sortAndSearch<Type>::firstOccurrence(Type list[], bool present[], int low, int high, Type searchItem, int n)
{
	if (high >= low)
	{
		int mid = low + (high - low) / 2;
		if ((mid == 0 || searchItem > list[mid - 1]) && (list[mid] == searchItem && present[mid] == true))
			return mid;
		else if (searchItem > list[mid])
			return firstOccurrence(list, present, (mid + 1), high, searchItem, n);
		else
			return firstOccurrence(list, present, low, (mid - 1), searchItem, n);
	}
	return -1;
}

template <class Type>
int sortAndSearch<Type>::lastOccurrence(Type list[], bool present[], int low, int high, Type searchItem, int n)
{
	if (high >= low)
	{
		int mid = low + (high - low) / 2;
		if ((mid == n - 1 || searchItem < list[mid + 1]) && (list[mid] == searchItem && present[mid] == true)) {
			return mid;
		}
		else if (searchItem < list[mid]) {
			return lastOccurrence(list,  present, low, (mid - 1), searchItem, n);
		}
		else {
			return lastOccurrence(list, present, (mid + 1), high, searchItem, n);
		}
	}
	else {
		return -1;
	}
	
}


template <class Type>
void sortAndSearch<Type>::reverseOrder(int ids[], Type list[], bool present[], int start, int end) {
	while (start < end) {
		Swap(ids, list, present, start, end);
		start++;
		end--;
	}
}


template <class Type>
void sortAndSearch<Type>::Swap(int ids[], Type list[], bool present[], int first, int second) {
	Type tempType;
	int tempInt;
	bool tempBool;

	tempType = list[first];
	list[first] = list[second];
	list[second] = tempType;

	tempInt = ids[first];
	ids[first] = ids[second];
	ids[second] = tempInt;

	tempBool = present[first];
	present[first] = present[second];
	present[second] = tempBool;
}


template <class Type>
int sortAndSearch<Type>::binarySearch(Type list[], bool present[], int first, int length,  Type searchItem) {
	int last = length - 1;
	int mid;
	bool found = false;

	while ((first <= last) && !found) {
		mid = (first + last) / 2;

		if (list[mid] == searchItem && present[mid] == true)
			found = true;
		else if (list[mid] > searchItem)
			last = mid - 1;
		else
			first = mid + 1;
	}
	if (found)
		return mid;
	else
		return -1;
}


template<class Type>
void sortAndSearch<Type>::heapify(int ids[],Type list[], bool present[], int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && list[l] > list[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && list[r] > list[largest])
		largest = r;

	// If largest is not root 
	if (largest != i) {
		Swap(ids, list, present, i, largest);

		// Recursively heapify the affected sub-tree 
		heapify(ids, list, present, n, largest);
	}
}

template<class Type>
void sortAndSearch<Type>::heapSort(int ids[], Type list[], bool present[], int n)
{
	// Build heap (relistange listay) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(ids, list, present, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--) {
		// Move current root to end 
		Swap(ids, list, present, 0, i);

		// call max heapify on the reduced heap 
		heapify(ids, list, present, i, 0);
	}
}