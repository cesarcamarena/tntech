package brass;

import java.awt.Graphics;
import java.util.List;

import gui.HotSpot;

public class BrassIndustry
{
	private int brass_industry_type;
	private BrassToken brass_token;
	private HotSpot industry_spot;
	
	public void draw(Graphics g, gui.DrawRectangle resource_cube, List<gui.PixelPoint> resource_cube_centers, gui.DrawOval flip_circle, gui.PixelPoint flip_circle_center)
	{
		if (brass_token != null)
		{
			brass_token.drawCityToken(g, resource_cube, resource_cube_centers, flip_circle, flip_circle_center);
		}
	}
	
	public void placeTokenInCity(BrassToken brass_token)
	{
		this.brass_token = brass_token;
		brass_token.moveTokenFromPlayerToCity(industry_spot.getHotX(), industry_spot.getHotY());
	}
	
	//some city locations can accept more than one industry type
	public boolean canCityAcceptIndustry(int industry_id)
	{
		if (brass_token != null) return false;  //already occupied by a token
		
		if (industry_id == brass_industry_type) return true;
		else if ((industry_id == 1 || industry_id == 2) && brass_industry_type == 6) return true;
		else if ((industry_id == 2 || industry_id == 4) && brass_industry_type == 7) return true;
		
		return false;
	}
	
	public BrassIndustry(int industry_type, HotSpot hot_spot)
	{ 
		brass_industry_type = industry_type;
		industry_spot = hot_spot;
		brass_token = null;
	}
	
	public int getVictoryPoints()
	{
		return brass_token.getVictoryPoints();
	}
	
	public int getPlayerID()
	{
		if (brass_token == null) return 0;
		return brass_token.getPlayerID();
	}
	
	public boolean isFlipped()
	{
		if (brass_token == null) return false;
		return brass_token.isFlipped();
	}
	
	public int getIndustryID()
	{
		return industry_spot.getHotSpotID();
	}
	
	public boolean isConstructed()
	{
		return (brass_token != null);
	}
	
	public boolean isIndustrySelected(int x, int y)
	{
		return industry_spot.isSelected(x, y);
	}
}
