package pqsort;

public interface PQInterface<E>
{
	/**
	Preconditions: Requires an item to be inserted.
	Postconditions: Inserts item into priority queue.
	Throws: PQException if something happened to the insertion.
	*/
	public void pqInsert(E item) throws PQException;

	/**
	Preconditions: None.
	Postconditions: Removes an item from the priority queue.
	Throws: PQException if there are no items in the priority queue.
	*/
	public E pqRemove() throws PQException;

	/**
	Preconditions: None.
	Postconditions: Returns whether the priority queue is empty or not.
	Throws: None.
	*/
	public boolean pqIsEmpty();
}