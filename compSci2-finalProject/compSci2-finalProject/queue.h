//Header file for queue 



#ifndef H_Queue 

#define H_Queue 



#include <iostream>  

#include <cassert> 



using namespace std;



template <class Type>
class queue
{

public:

	const queue<Type>& operator=(const queue<Type>&);

	//Overload the assignment operator. 



	bool isEmptyQueue() const;

	//Function to determine whether the queue is empty. 

	//Postcondition: Returns true if the queue is empty, 

	//               otherwise returns false. 



	bool isFullQueue() const;

	//Function to determine whether the queue is full. 

	//Postcondition: Returns true if the queue is full, 

	//               otherwise returns false. 



	void initializeQueue();

	//Function to initialize the queue to an empty state. 

	//Postcondition: count = 0; queueFront = 0; 

	//               queueRear = maxQueueSize – 1 



	Type front() const;

	//Function to return the first element of the queue. 

	//Precondition: The queue exists and is not empty. 

	//Postcondition: If the queue is empty, the program  

	//               terminates; otherwise, the first  

	//               element of the queue is returned.   

	Type back() const;

	//Function to return the last element of the queue. 

	//Precondition: The queue exists and is not empty. 

	//Postcondition: If the queue is empty, the program  

	//               terminates; otherwise, the last  

	//               element of the queue is returned. 



	void addQueue(const Type& queueElement);

	//Function to add queueElement to the queue. 

	//Precondition: The queue exists and is not full. 

	//Postcondition: The queue is changed and queueElement 

	//               is added to the queue. 



	void deleteQueue();

	//Function to remove the first element of the queue. 

	//Precondition: The queue exists and is not empty. 

	//Postcondition: The queue is changed and the first  

	//               element is removed from the queue. 



	queue(int queueSize = 100);

	//Constructor 



	queue(const queue<Type>& otherQueue);

	//Copy constructor 



	~queue();

	//Destructor 



	void moveNthFront(int n);



private:

	int maxQueueSize; //variable to store the maximum queue size 

	int count;        //variable to store the number of 

	  //elements in the queue 

	int queueFront;   //variable to point to the first 

	  //element of the queue 

	int queueRear;    //variable to point to the last 

	  //element of the queue 

	Type* list;       //pointer to the array that holds  

	  //the queue elements  

};



template <class Type>
void  queue<Type>::moveNthFront(int n) {

	Type temp = list[n];

	list[n] = list[queueFront];

	list[queueFront] = temp;

}

//Add definition for overloaded assignment operator 
template <class Type>
const queue<Type>& queue<Type>::operator=(const queue<Type>& otherQueue) {

	if (this != &otherQueue) { //avoid self-copy 

		delete[] list;

		maxQueueSize = otherQueue.maxQueueSize;

		count = otherQueue.count;

		queueFront = otherQueue.queueFront;

		queueRear = otherQueue.queueRear;



		list = new Type[maxQueueSize];



		//copy otherStack into this stack 

		for (int j = 0; j <= queueRear; j++)

			list[j] = otherQueue.list[j];

	}
	return *this;
}

//Add definition for copy constructor 
template <class Type>
queue<Type>::queue(const queue<Type>& otherQueue) {

	list = nullptr;



	if (this != &otherQueue) { //avoid self-copy 

		delete[] list;

		maxQueueSize = otherQueue.maxQueueSize;

		count = otherQueue.count;

		queueFront = otherQueue.queueFront;

		queueRear = otherQueue.queueRear;



		list = new Type[maxQueueSize];



		//copy otherStack into this stack 

		for (int j = 0; j <= queueRear; j++)

			list[j] = otherQueue.list[j];

	}



}



template <class Type>
bool queue<Type>::isEmptyQueue() const
{

	return (count == 0);

} //end isEmptyQueue 



template <class Type>
bool queue<Type>::isFullQueue() const
{

	return (count == maxQueueSize);

} //end isFullQueue 



template <class Type>
void queue<Type>::initializeQueue()

{

	queueFront = 0;

	queueRear = maxQueueSize - 1;

	count = 0;

} //end initializeQueue 



template <class Type>
Type queue<Type>::front() const
{
	assert(!isEmptyQueue());
	return list[queueFront];
} //end front 



template <class Type>
Type queue<Type>::back() const

{

	assert(!isEmptyQueue());

	return list[queueRear];

} //end back 



template <class Type>
void queue<Type>::addQueue(const Type& newElement)
{
	if (!isFullQueue())
	{

		queueRear = (queueRear + 1) % maxQueueSize; //use mod 

		//operator to advance queueRear   

		//because the array is circular 

		count++;

		list[queueRear] = newElement;

	}else
		cerr << "Cannot add to a full queue." << endl;

} //end addQueue 



template <class Type>
void queue<Type>::deleteQueue()
{
	if (!isEmptyQueue())
	{
		count--;

		queueFront = (queueFront + 1) % maxQueueSize; //use the 

		//mod operator to advance queueFront  

		//because the array is circular  

	}else
		cerr << "Cannot remove from an empty queue." << endl;

} //end deleteQueue 



//Constructor 
template <class Type>
queue<Type>::queue(int queueSize)
{
	if (queueSize <= 0)
	{
		cerr << "Size of the array to hold the queue must "

			<< "be positive." << endl;

		cerr << "Creating an array of size 100." << endl;
		maxQueueSize = 100;

	}
	else
		maxQueueSize = queueSize;   //set maxQueueSize to  
		//queueSize 
	queueFront = 0;                 //initialize queueFront 

	queueRear = maxQueueSize - 1;   //initialize queueRear 
	count = 0;
	list = new Type[maxQueueSize];  //create the array to 
	//hold the queue elements 
} //end constructor 



//Destructor 
template <class Type>
queue<Type>::~queue()
{
	delete[] list;
} //end destructor 
#endif 



