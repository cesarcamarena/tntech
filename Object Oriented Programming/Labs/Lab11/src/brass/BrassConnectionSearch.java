package brass;

import java.util.List;

abstract class BrassConnectionSearch implements BrassConnectionSearchInterface
{
	protected List<BrassConnection> brass_connections;

	public BrassConnectionSearch(List<BrassConnection> brass_connections)
	{
		this.brass_connections = brass_connections;
	}

	protected int isLinkConnected(int city_id, int[] connected_cities) //changed from private to protected
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

	public abstract table.TableInterface<Integer, Integer> connectionSearch(int start_city_id, table.Comparator<Integer, Integer> comp_city_ids);

}