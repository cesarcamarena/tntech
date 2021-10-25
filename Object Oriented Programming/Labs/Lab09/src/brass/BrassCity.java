package brass;

import java.awt.Graphics;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

class BrassCity
{
	private int brass_city_id;
	private String brass_city_name;
	private List<BrassIndustry> brass_industries;
	
	public void placeTokenInCity(BrassToken brass_token)
	{
		for (BrassIndustry brass_industry : brass_industries)
		{
			boolean can_accept = brass_industry.canCityAcceptIndustry(brass_token.getIndustryID());
			if (can_accept)
			{
				brass_industry.placeTokenInCity(brass_token);
				return;
			}
		}
		//lab 8 assert
		assert false : "City cannot accommodate the requested industry.";
	}
	
	public boolean canCityAcceptIndustry(int industry_id)
	{
		Iterator<BrassIndustry> brass_industry_iter = brass_industries.iterator();
		while (brass_industry_iter.hasNext())
		{
			BrassIndustry brass_industry = brass_industry_iter.next();
			boolean can_accept = brass_industry.canCityAcceptIndustry(industry_id);
			if (can_accept) return true;
		}
		return false;
	}
	
	public void draw(Graphics g, gui.DrawRectangle resource_cube, List<gui.PixelPoint> resource_cube_centers, gui.DrawOval flip_circle, gui.PixelPoint flip_circle_center)
	{
		Iterator<BrassIndustry> industry_iter = brass_industries.iterator();
		while(industry_iter.hasNext())
		{
			BrassIndustry brass_industry = industry_iter.next();
			brass_industry.draw(g, resource_cube, resource_cube_centers, flip_circle, flip_circle_center);
		}
	}
	
	public BrassCity(int city_id, String city_name)
	{
		brass_city_id = city_id;
		brass_city_name = city_name;
		brass_industries = new ArrayList<BrassIndustry>();
	}
	
	//no city has more than 4 industry locations
	public void addIndustry(BrassIndustry brass_industry)
	{
		brass_industries.add(brass_industry);
		assert (brass_industries.size() <= 4) : "Add brass industry error.";
	}
	
	public boolean isCitySelected(int x, int y)
	{
		Iterator<BrassIndustry> industry_iter = brass_industries.iterator();
		while(industry_iter.hasNext())
		{
			BrassIndustry brass_industry = industry_iter.next();
			if (brass_industry.isIndustrySelected(x, y))
			{
				return true;
			}
		}
		
		return false;
	}
	
	//a player cannot have more than 4 tokens in a city (limited by number of industries)
	public int getNumTokensInCity(int player_id)
	{
		int count = 0;
		Iterator<BrassIndustry> industry_iter = brass_industries.iterator();
		while(industry_iter.hasNext())
		{
			BrassIndustry brass_industry = industry_iter.next();
			if (brass_industry.getPlayerID() == player_id)
			{
				count++;
			}
		}
		
		assert (count <= 4) : "Number of tokens in city error.";
		return count;
	}
	
	public boolean isCityFull()
	{
		for (BrassIndustry brass_industry : brass_industries)
		{
			if (!brass_industry.isConstructed()) return false;
		}
		return true;
	}
	
	public int getCityID()
	{
		return brass_city_id;
	}
	
	public String getCityName()
	{
		return brass_city_name;
	}
	
	public int getSelectedIndustry(int x, int y)
	{
		Iterator<BrassIndustry> industry_iter = brass_industries.iterator();
		
		while(industry_iter.hasNext())
		{
			BrassIndustry brass_industry = industry_iter.next();
			boolean industry_selected = brass_industry.isIndustrySelected(x, y);
			if (industry_selected)
			{
				return brass_industry.getIndustryID();
			}
		}
		
		return 0;
	}
}
