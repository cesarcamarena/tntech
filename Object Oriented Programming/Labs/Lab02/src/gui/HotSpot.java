package gui;

/**
	HotSpot defines a rectangular area centered at a specified location on the screen. 
	Given a location (x,y), HotSpot determines whether that location is within the rectangular area.
*/
public class HotSpot
{
	private int spot_id;
	private int x_loc;
	private int y_loc;
	private int width;
	private int height;
	
	/**
		The centered location (x,y) and dimensions (w,h) of the HotSpot are passed to the constructor.
	*/
	public HotSpot(int hot_id, int x, int y, int w, int h)
	{
		spot_id = hot_id;
		x_loc = x;
		y_loc = y;
		width = w;
		height = h;
	}
	
	public void setHotX(int x)
	{
		x_loc = x;
	}
	
	public void setHotY(int y)
	{
		y_loc = y;
	}

	public int getHotX()
	{
		return x_loc;
	}
	
	public int getHotY()
	{
		return y_loc;
	}
	
	public int getHotWidth()
	{
		return width;
	}
	
	public int getHotHeight()
	{
		return height;
	}
	
	public int getHotLeft()
	{
		return x_loc - width/2;
	}
	
	public int getHotTop()
	{
		return y_loc - height/2;
	}
	
	/**
		Returns whether the provided (x,y) is within the hot spot area.
	*/
	public boolean isSelected(int x_click, int y_click)
	{
		int x_hit = Math.abs(x_click - x_loc);
		int y_hit = Math.abs(y_click - y_loc);
		if (x_hit < (width/2) && y_hit < (height/2))
		{
			return true;
		}

		return false;
	}
	
	public int getHotSpotID()
	{
		return spot_id;
	}
}
