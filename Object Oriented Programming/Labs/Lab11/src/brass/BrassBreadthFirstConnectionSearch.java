package brass;

import java.util.List;
import java.util.Iterator;
import util.QueueLinked;

public class BrassBreadthFirstConnectionSearch extends BrassConnectionSearch//implements BrassConnectionSearchInterface
{
	//private List<BrassConnection> brass_connections;

	public BrassBreadthFirstConnectionSearch(List<BrassConnection> brass_connections)
	{
		//this.brass_connections = brass_connections;

		super(brass_connections);
	}

	public table.TableInterface<Integer, Integer> connectionSearch(int start_city_id, table.Comparator<Integer, Integer> comp_city_ids)
	{
		//the queue for breadth first search
		QueueLinked<Integer> city_queue = new QueueLinked<Integer>();
		
		//the first location to check is in the same city as the build action
		city_queue.enqueue(new Integer(start_city_id));
		table.TableInterface<Integer, Integer> explored_cities = table.TableFactory.createTable(comp_city_ids);
		explored_cities.tableInsert(new Integer(start_city_id));
		
		//add to the end of city_queue and remove from front for FIFO behavior
		while(city_queue.size() > 0)
		{
			int next_city_id = city_queue.dequeue();
			getConnectedCities(next_city_id, explored_cities, city_queue);
		}
		
		return explored_cities;
	}

	private void getConnectedCities(int city_id, table.TableInterface<Integer, Integer> explored_cities, QueueLinked<Integer> queue)
	{
		Iterator<BrassConnection> brass_connection_iter = brass_connections.iterator();
		while(brass_connection_iter.hasNext())
		{
			BrassConnection brass_connection = brass_connection_iter.next();
			if (brass_connection.isLinkConstructed())
			{
				int[] connected_cities = brass_connection.getConnectedCities();
				int test_city_id = isLinkConnected(city_id, connected_cities);
				if (test_city_id == 0) continue;  //this canal is not connected to the city
				
				try
				{
					explored_cities.tableInsert(new Integer(test_city_id));
					queue.enqueue(new Integer(test_city_id));
				}
				catch(table.TableException te)
				{
					//ignore duplicate
				}
			}
		}
	}

	/*
	private int isLinkConnected(int city_id, int[] connected_cities)
	{
		int test_city_id = 0;
		//is this canal connected to the current city?
		if (connected_cities[0] == city_id)
		{
			test_city_id = connected_cities[1];
		}
		else if (connected_cities[1] == city_id)
		{
			test_city_id = connected_cities[0];
		}
		
		return test_city_id;
	}
	*/

}