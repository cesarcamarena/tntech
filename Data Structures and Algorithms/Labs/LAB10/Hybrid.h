/*
	Cesar Camarena
	Jig Patel
	Lab 10
*/
#if !defined (HYBRID_H)
#define HYBRID_H

#include "QueueLinked.h"
using CSC2110::QueueLinked;
#include "SortedListDoublyLinked.h"

template < class T >
class Hybrid
{

   private:
      QueueLinked< DoubleNode<T> >* q;
      SortedListDoublyLinked<T>* sldl;

   public:
      Hybrid(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~Hybrid();

      bool isEmpty();
      void enqueue(T* item);
      T* dequeue();
      ListDoublyLinkedIterator<T>* iterator();

};

template < class T >
Hybrid<T>::Hybrid(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   q = new QueueLinked< DoubleNode<T> >();
   sldl = new SortedListDoublyLinked<T>(comp_items, comp_keys);
}

template < class T >
Hybrid<T>::~Hybrid()
{
   delete q;
   delete sldl;
}

//DO THIS
//complete the implementation for the Hybrid ADT in two different ways
//as outlined in the Lab 10 description
//simply comment the first implementation out when working on the second implementation
//use the getKey method to dequeue/remove

template < class T >
bool Hybrid<T>::isEmpty()
{
	return q->size();
}

/* EASY METHOD
template < class T >
void Hybrid<T>::enqueue(T* item)
{
	q->enqueue(item);
	sldl->add(item);
}

template < class T >
T* Hybrid<T>::dequeue()
{
	T* item = q->dequeue();
	
	String* key = getKey();
	
	sldl->remove(key);
	
	return item;
}
*/

template < class T >
void Hybrid<T>::enqueue(T* item)
{
	DoubleNode<T>* dn = sldl->addDN(item);
	q->enqueue(dn);
}

template < class T >
T* Hybrid<T>::dequeue()
{
	DoubleNode<T>* dn = q->dequeue();
	T* item = sldl->remove(dn);
	return item;
}

template < class T >
ListDoublyLinkedIterator<T>* Hybrid<T>::iterator()
{
	ListDoublyLinkedIterator<T>* iter = sldl->iterator();
	
	return iter;
}




#endif
