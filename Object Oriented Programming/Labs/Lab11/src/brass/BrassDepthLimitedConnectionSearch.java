package brass;

import java.util.List;
import java.util.Iterator;

public class BrassDepthLimitedConnectionSearch extends BrassConnectionSearch//implements BrassConnectionSearchInterface
{
	//private List<BrassConnection> brass_connections;
	private int depth_limit;

	public BrassDepthLimitedConnectionSearch(List<BrassConnection> brass_connections, int depth_limit)
	{
		//this.brass_connections = brass_connections;

		super(brass_connections);

		this.depth_limit = depth_limit;
	}

	public table.TableInterface<Integer, Integer> connectionSearch(int start_city_id, table.Comparator<Integer, Integer> comp_city_ids)
	{
		table.TableInterface<Integer, Integer> explored_cities = table.TableFactory.createTable(comp_city_ids);
	
		if (depth_limit < 0) depth_limit = 0;
		int current_depth = 0;

		explored_cities.tableInsert(new Integer(start_city_id));
		
		if (current_depth < depth_limit)
		{
			depthLimitedRec(start_city_id, current_depth + 1, depth_limit, explored_cities);
		}
		
		return explored_cities;
	}

	private void depthLimitedRec(int city_id, int current_depth, int depth_limit, table.TableInterface<Integer, Integer> explored_cities)
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
					if (current_depth < depth_limit)
					{
						depthLimitedRec(test_city_id, current_depth + 1, depth_limit, explored_cities);
					}
				}
				catch(table.TableException te)
				{
					//ignore cities already visited
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