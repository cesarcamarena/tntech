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
	protected ArrayList<BrassConnection> brass_connections;
	protected List<Image> brass_connection_images;
	protected PixelDimension brass_connection_dimension;
	
	public int getSelectedLink(int x, int y)
	{
		Iterator<BrassConnection> iter = brass_connections.iterator();

		while (iter.hasNext())
		{
			BrassConnection bc = iter.next();

			if (bc.isSelected(x, y) && !bc.isConstructed())
			{
				return bc.getConnectionID();
			}
		}

		return 0;
	}
	
	public void draw(Graphics g)
	{
		Iterator<BrassConnection> iter = brass_connections.iterator();

		while (iter.hasNext())
		{
			BrassConnection bc = iter.next();

			bc.draw(g);
		}
		
		
	}
	
	public int getNumLinks()
	{
		return brass_connections.size();
	}
	
	public void constructLink(int link_id, int player_id)
	{
		if (isConstructed(link_id)) return;

		BrassConnection brass_connection = brass_connections.get(link_id - 1);
		DrawImage brass_connection_img = new DrawImage(brass_connection_images.get(player_id - 1), "Brass Canal " + link_id, brass_connection_dimension.getWidth(), brass_connection_dimension.getHeight());
		brass_connection.constructLink(player_id, brass_connection_img);
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
}