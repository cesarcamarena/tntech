/*
	Name: Cesar Camarena
	Purpose: Program 2
*/
#if !defined NULL
#define NULL 0
#endif

#if !defined (QUEUEDEQUE_H)
#define QUEUEDEQUE_H

#include "DequeArray.h"

template < class T >
class QueueDeque
{
	private:
		DequeArray<T>* queueDeque;
		
	public:
	  /*pre: Nothing.
	    post: Constructs the QueueDeque array.*/
		QueueDeque();
		
	  /*pre: Nothing.
	    post: Deconstructs the QueueDeque array.*/
		~QueueDeque();
		
	  /*pre: Nothing.
	    post: Returns the current size of the array.*/
		int size();
		
	  /*pre: Nothing.
	    post: Returns true or false whether the size of the array is = 0*/
		bool isEmpty();
		
	  /*pre: Nothing.
	    post: Dequeues everything that is inside of the array.*/
		void dequeueAll();
		
	  /*pre: Nothing.
	    post: Returns the item that is at the back of the array.*/
		T* peek();
		
	  /*pre: An item that the user wants to insert at the back of the array.
	    post: Item is inserted at the back of the array.*/
		void enqueue(T* item);
		
	  /*pre: Nothing.
	    post: Returns the item that was removed at the back of the array.*/
		T* dequeue();
		
};

template < class T >
QueueDeque<T>::QueueDeque()
{
	queueDeque = new DequeArray<T>();
}

template < class T >
QueueDeque<T>::~QueueDeque()
{
	queueDeque->~DequeArray();
}

template < class T >
int QueueDeque<T>::size()
{
	return queueDeque->size();
}

template < class T >
bool QueueDeque<T>::isEmpty()
{
	return queueDeque->isEmpty();
}

template < class T >
void QueueDeque<T>::dequeueAll()
{
	queueDeque->dequeueAll();
}

template < class T >
T* QueueDeque<T>::peek()
{
	return queueDeque->peek();
}

template < class T >
void QueueDeque<T>::enqueue(T* item)
{
	queueDeque->enqueue(item);
}

template < class T >
T* QueueDeque<T>::dequeue()
{
	return queueDeque->dequeue();
}

#endif