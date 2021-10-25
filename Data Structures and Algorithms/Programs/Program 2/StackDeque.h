/*
	Name: Cesar Camarena
	Purpose: Program 2
*/
#if !defined NULL
#define NULL 0
#endif

#if !defined (STACKDEQUE_H)
#define STACKDEQUE_H

#include "DequeArray.h"

template < class T >
class StackDeque
{
	private:
		DequeArray<T>* stackDeque;
		
	public:
      /*pre: Nothing.
	    post: Constructs the stackDeque array*/
		StackDeque();
		
	  /*pre: Nothing.
	    post: Deconstructs the stackDeque array*/
		~StackDeque();
		
	  /*pre: Nothing.
	    post: Returns the size of the array.*/
		int size();
		
	  /*pre: Nothing.
	    post: Returns true or false whether the size of the array is = 0*/
		bool isEmpty();
		
	  /*pre: Nothing.
	    post: Pops everything that is inside of the stackDeque array*/
		void popAll();
		
	  /*pre: Nothing.
	    post: Returns the item that is at the front of the array.*/
		T* peek();
		
	  /*pre: An item that the user wants to insert at the front of the array.
	    post: Item is inserted at the front of the array.*/
		void push(T* item);
		
	  /*pre: Nothing.
	    post: Returns the item that was removed at the front of the array.*/
		T* pop();
		
};

template < class T >
StackDeque<T>::StackDeque()
{
	stackDeque = new DequeArray<T>();
}

template < class T >
StackDeque<T>::~StackDeque()
{
	stackDeque->~DequeArray();
}

template < class T >
int StackDeque<T>::size()
{
	stackDeque->size();
}

template < class T >
bool StackDeque<T>::isEmpty()
{
	return stackDeque->isEmpty();
}

template < class T >
void StackDeque<T>::popAll()
{
	return stackDeque->dequeueAll();
}

template < class T >
T* StackDeque<T>::peek()
{
	return stackDeque->peek();
}

template < class T >
void StackDeque<T>::push(T* item)
{
	stackDeque->enqueueDeque(item);
}

template < class T >
T* StackDeque<T>::pop()
{
	return stackDeque->dequeue();
}

#endif