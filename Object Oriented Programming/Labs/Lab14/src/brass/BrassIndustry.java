package brass;

import java.awt.Graphics;
import java.util.List;

import gui.HotSpot;

public class BrassIndustry
{
	private int brass_industry_type;
	private BrassToken brass_token;
	private HotSpot industry_spot;
	
	//overwrites a token
	public void replaceTokenInCity(BrassToken replace_token)
	{
		assert brass_token != null : "Not a replacement operation.";
		this.brass_token = replace_token;
		replace_token.moveTokenFromPlayerToCity(industry_spot.getHotX(), industry_spot.getHotY());
	}
	
	public boolean canCityReplaceIndustry(BrassToken replace_token)
	{
		if (brass_token == null) return false;
		
		boolean player_id_okay = brass_token.getPlayerID() == replace_token.getPlayerID();
		boolean industry_id_okay = brass_token.getIndustryType() == replace_token.getIndustryType();
		boolean tech_level_okay = brass_token.getTechLevel() < replace_token.getTechLevel();
		return player_id_okay && industry_id_okay && tech_level_okay;
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
	
	public void clearLevel1Industry()
	{
		if (brass_token != null && brass_token.getTechLevel() == 1)
		{
			brass_token = null;  //remove tech level 1 industries from the board
		}
	}
	
	public int getTechLevel()
	{
		if (brass_token == null) return -1;
		return brass_token.getTechLevel();
	}
	
	public int getIncome()
	{
		if (brass_token == null) return 0;
		return brass_token.getIncome();
	}
	
	public void flipIndustry()
	{
		if (brass_token == null) return;
		brass_token.flipToken();
	}
	
	public boolean isUnflippedIndustry(int industry_id)
	{
		if (isIndustryConstructed() && !isFlipped() && (getIndustryType() == industry_id))
		{
			return true;
		}
		
		return false;
	}
	
	public boolean isConstructedPort()
	{		
		if (isIndustryConstructed() && (getIndustryType() == BrassIndustryEnum.PORT.getValue()))
		{
			return true;
		}
		
		return false;
	}
	
	public boolean isIndustryConstructed()
	{
		return (brass_token != null);
	}
	
	public int getNumCubes()
	{
		if (brass_token == null) return 0;
		return brass_token.getNumCubes();
	}
	
	public int getIndustryType()
	{
		if (brass_token == null) return 0;
		return brass_token.getIndustryType();
	}

	public void removeCube(BrassPlayers brass_players, BrassTrack brass_track)
	{
		assert brass_token != null : "No cubes to remove.";
		brass_token.removeCube(brass_players, brass_track);
	}
	
	public void draw(Graphics g, gui.DrawRectangle resource_cube, List<gui.PixelPoint> resource_cube_centers, gui.DrawOval flip_circle, gui.PixelPoint flip_circle_center)
	{
		if (brass_token != null)
		{
			brass_token.drawCityToken(g, resource_cube, resource_cube_centers, flip_circle, flip_circle_center);
		}
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
	
	public boolean isIndustrySelected(int x, int y)
	{
		return industry_spot.isSelected(x, y);
	}
	
	org.jdom2.Element writeXML()
   {
	   org.jdom2.Element industry_element = new org.jdom2.Element("industry");
	  if (brass_token != null)
	  {
		  org.jdom2.Element token_element = brass_token.writeXML();
		  industry_element.addContent(token_element);
	  }

      return industry_element;
   }

	void readXML(org.jdom2.Element industry_element, BrassPlayers brass_players)
	{	
		brass_token = null;
		org.jdom2.Element token_element = industry_element.getChild("token");
		if (token_element != null)
		{

			org.jdom2.Element player_id_element = token_element.getChild("player_id");
			int player_id = Integer.parseInt(player_id_element.getText());
			
			org.jdom2.Element token_id_element = token_element.getChild("token_id");
			int token_id = Integer.parseInt(token_id_element.getText());
			
			brass_token = brass_players.getBrassToken(player_id, token_id);
			brass_token.readXML(token_element);
			brass_token.moveTokenFromPlayerToCity(industry_spot.getHotX(), industry_spot.getHotY());
		}
	}
}
