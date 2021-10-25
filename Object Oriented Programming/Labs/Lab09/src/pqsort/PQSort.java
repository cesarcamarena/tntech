package pqsort;

import java.util.List;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.Iterator;

public class PQSort
{
	/**
    Preconditions:	Needs an unsorted list of items, comparator, and priority queue pq_type
				    enumeration to implement sorting method.
    Postconditions: Returns a sorted list of items, however the original unsorted list of
				    items were untouched.
    Throws: None.
    */
	public static <E> List<E> pqSort(List<E> unsorted_items, Comparator<E> comp, PQType pq_type)
	{
		List<E> sorted_items = new ArrayList<E>();

		PQInterface<E> pq = PQFactory.createPQ(comp, pq_type);

		Iterator<E> iter = unsorted_items.iterator();

		while (iter.hasNext())
		{
			E item = iter.next();

			pq.pqInsert(item);
		}

		while (!pq.pqIsEmpty())
		{
			E item = pq.pqRemove();

			sorted_items.add(item);
		}

		return sorted_items;
	}
}