package pqsort;

import java.util.Comparator;

public class PQFactory 
{
	/**
    Preconditions:	Needs a comparator and what type of priority queue wanted based from
				    the priority queue type enumeration.
    Postconditions: Returns a priority queue depending what type of priority queue was
				    passed to the parameter list.
    Throws: None.
    */
	public static <E> PQInterface<E> createPQ(Comparator<E> comp, PQType pq_type)
	{
		if (pq_type == PQType.TREE)
		{
			return new PQBST<E>(comp);
		}

		else
		{
			return new PQSLL<E>(comp);
		}
	}
}