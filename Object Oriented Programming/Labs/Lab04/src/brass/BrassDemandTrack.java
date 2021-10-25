package brass;

import java.awt.Graphics;

import java.util.List;
import java.util.ArrayList;

import gui.PixelPoint;
import gui.PixelDimension;
import gui.DrawImage;

public class BrassDemandTrack
{
	//DO THIS
	//declare a buy_stack and a sell_stack using type BrassDemandTrackItem
	private util.StackLinked<BrassDemandTrackItem> buy_stack;
	
	private util.StackLinked<BrassDemandTrackItem> sell_stack;
	
	
	//DO THIS
	//complete these methods
	public boolean canSellToDemandTrack()
	{
		return !(sell_stack.isEmpty());

	}
	
	//check that a sale is possible first
	//return the amount from the BrassDemandTrackItem moved from sell to buy
	public int sellToDemandTrack()
	{
		if(sell_stack.isEmpty())
		{
			return 0;
		}
		else
		{
			BrassDemandTrackItem item = sell_stack.pop();
			
			int amount = item.getAmount();
			
			return amount;
		}
	}
	
	public int getCostToBuyFromDemandTrack()
	{
		BrassDemandTrackItem item = buy_stack.peek();
		
		int cost = item.getAmount();
		
		return cost;
	}
	
	//the last item is never popped
	public void buyFromDemandTrack()
	{	
		if (buy_stack.size() == 1)
		{
			BrassDemandTrackItem item = buy_stack.peek();

			sell_stack.push(item);
		}
		else
		{
			BrassDemandTrackItem item = buy_stack.pop();

			sell_stack.push(item);
		}
	}
	
	public static int getBrassDemandTrackValue(int demand_index)
	{
		if (demand_index > 8 || demand_index < 0) return 0;
		return ((9 - demand_index) + 1)/2;
	}
	
	public BrassDemandTrack(java.awt.Image track_img, PixelDimension track_dim, List<PixelPoint> track_centers)
	{
		//DO THIS
		buy_stack = new util.StackLinked<BrassDemandTrackItem>();
		sell_stack = new util.StackLinked<BrassDemandTrackItem>();
		
		BrassDemandTrackItem demand_track_bottom_item = new BrassDemandTrackItem(0, getBrassDemandTrackValue(0), null, null);
		buy_stack.push(demand_track_bottom_item);  //no image
		
		int track_size = track_centers.size();  //8 locations
		for (int i = 1; i <= track_size; i++)
		{
			DrawImage track_marker = new DrawImage(track_img, "Demand Marker", track_dim.getWidth(), track_dim.getHeight());
			BrassDemandTrackItem demand_track_item = new BrassDemandTrackItem(0, getBrassDemandTrackValue(i), track_centers.get(track_size - i), track_marker);
			buy_stack.push(demand_track_item);
			demand_track_item.showDemandTrackImage();
		}
	}
	
	public void draw(Graphics g)
	{
		util.StackLinked<BrassDemandTrackItem> draw_stack = new util.StackLinked<BrassDemandTrackItem>();
		while(buy_stack.size() > 1)  //bottom item not drawn
		{
			BrassDemandTrackItem item = buy_stack.pop();
			item.draw(g);
			draw_stack.push(item);
		}
		
		while(!draw_stack.isEmpty())
		{
			buy_stack.push(draw_stack.pop());
		}
	}
}
