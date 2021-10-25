package brass;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import java.awt.Graphics;
import java.awt.Image;

import gui.HotSpot;
import gui.DrawImage;
import gui.ImageLoader;
import gui.PixelPoint;
import gui.PixelDimension;

import util.QueueLinked;

abstract class BrassConnections
{
	protected List<BrassConnection> brass_connections;
	protected List<Image> brass_connection_images;
	protected PixelDimension connection_dimension;
	
	public void buildLink(int link_id, int player_id)
	{
		//lab 8 assert
		assert !isConstructed(link_id) : "Link already constructed.";

		BrassConnection brass_connection = brass_connections.get(link_id - 1);
		DrawImage brass_connection_img = new DrawImage(brass_connection_images.get(player_id - 1), "Brass Canal " + link_id, connection_dimension.getWidth(), connection_dimension.getHeight());
		brass_connection.buildLink(player_id, brass_connection_img);
	}
	
	//not necessary to find the closest match
	//get all connected cities from target city
	public table.TableInterface<Integer, Integer> breadthFirstConnections(int start_city_id, table.Comparator<Integer, Integer> comp_city_ids)
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
	
	//puts all of the connected cities on a queue
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
	
	//keep calling the method below with an increasing depth
	//until whatever is being searched for is found or the depth limit is reached
	//in this starting case, want a city that contains a coal token with cubes still on it
	//simply look through the returned list to see if that city is present
	//also want to give preference to the current player's coal token if possible
	
	//a depth of zero will return the current city by itself
	public table.TableInterface<Integer, Integer> depthLimitedConnections(int start_city_id, int depth_limit, table.Comparator<Integer, Integer> comp_city_ids)
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
	
	//if one end of the link matches the city_id parameter, return the city_id of the other end
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
	
	public boolean isLinkConstructed(int link_id)
	{
		BrassConnection brass_connection = brass_connections.get(link_id - 1);
		return brass_connection.isLinkConstructed();
	}
	
	public boolean doesPlayerHaveLinkIntoCity(int city_id, int player_id)
	{
		Iterator<BrassConnection> connection_iter = brass_connections.iterator();
		while(connection_iter.hasNext())
		{
			BrassConnection brass_connection = connection_iter.next();
			if (brass_connection.isLinkConstructed())
			{
				int p_id = brass_connection.getPlayerID();
				if (p_id == player_id)
				{
					int[] connected_cities = brass_connection.getConnectedCities();
					
					int city_1_id = connected_cities[0];
					int city_2_id = connected_cities[1];
					
					if (city_1_id == city_id || city_2_id == city_id)
					{
						return true;
					}
				}
			}
		}
		
		return false;
	}
	
	public int getNumLinks()
	{
		return brass_connections.size();
	}
	
	public void draw(Graphics g)
	{
		Iterator<BrassConnection> connections_iter = brass_connections.iterator();
		while (connections_iter.hasNext())
		{
			BrassConnection brass_connection = connections_iter.next();
			brass_connection.draw(g);
		}
	}
	
	public boolean isConstructed(int link_id)
	{
		BrassConnection brass_connection = brass_connections.get(link_id - 1);
		return brass_connection.isConstructed();
	}
	
	public int[] getConnectedCities(int link_id)
	{
		BrassConnection brass_connection = brass_connections.get(link_id - 1);
		return brass_connection.getConnectedCities();
	}
	
	public int getSelectedLink(int x, int y)
	{
		Iterator<BrassConnection> brass_connections_iter = brass_connections.iterator();
		while(brass_connections_iter.hasNext())
		{
			BrassConnection brass_connection = brass_connections_iter.next();
			if (brass_connection.isSelected(x, y) && !brass_connection.isConstructed())
			{
				return brass_connection.getConnectionID();
			}
		}
		
		return 0;
	}
}
