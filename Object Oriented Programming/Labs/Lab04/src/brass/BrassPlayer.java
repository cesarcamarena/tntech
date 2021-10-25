package brass;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;

import gui.DrawImage;
import gui.DrawFont;
import gui.PixelPoint;
import gui.PixelDimension;

class BrassPlayer
{
	private BrassHand brass_hand;
	private BrassTokens brass_tokens;
	
	private int player_id;
	private int amount_spent;
	private int money;
	
	private DrawFont verdana_bold_amount_spent;
	private DrawFont verdana_bold_money;
	
	private DrawImage player_canal_img;
	private DrawImage player_rail_img;
	
	private DrawImage player_turn_img;
	
	public int getSelectedCard(int x, int y)
	{
		return brass_hand.getSelectedCard(x, y);
	}
	
	public void draw(Graphics g, int active_player_id, int view_player_id)
	{
		if (active_player_id == player_id)
		{
			brass_hand.draw(g);  //only active player's hand should ever be displayed
			//only one of the following two images will actually be drawn
			player_canal_img.draw(g);
			player_rail_img.draw(g);
		}
		
		player_turn_img.draw(g);
		
		if (amount_spent < 10)  //draw everyone's amount spent
		{
			verdana_bold_amount_spent.draw(g, " " + amount_spent + "");
		}
		else
		{
			verdana_bold_amount_spent.draw(g, amount_spent + "");
		}
		
		if (view_player_id == player_id)
		{
			brass_tokens.draw(g);  //draw the view player's tokens
			
			if (money < 10)  //draw the view player's money
			{
				verdana_bold_money.draw(g, " " + money + "");
			}
			else
			{
				verdana_bold_money.draw(g, money + "");
			}
		}
	}
	
	//1 = red, 2 = purple, 3 = green, 4 = yellow
	public BrassPlayer(int p_id, BrassXML brass_xml, String color, PixelPoint amount_spent_loc)
	{
		gui.ImageLoader il = gui.ImageLoader.getImageLoader();

		player_id = p_id;
		amount_spent = 0;
		money = 30;
		brass_hand = new BrassHand(brass_xml);
		
		PixelPoint money_loc = brass_xml.getPixelCenter("money");
		int money_size = brass_xml.getTextSize("money");
		int amount_spent_size = brass_xml.getTextSize("amount_spent");
		
		verdana_bold_money = new DrawFont("Verdana", "bold", money_size, new Color(0,0,0), money_loc.getX(), money_loc.getY());
		verdana_bold_amount_spent = new DrawFont("Verdana", "bold", amount_spent_size, new Color(0,0,0), amount_spent_loc.getX(), amount_spent_loc.getY());
		
		PixelDimension link_dimension = brass_xml.getPixelDimension("link");
		PixelPoint link_location = brass_xml.getPixelCenter("link");
		PixelDimension player_dimension = brass_xml.getPixelDimension("circle");
		
		player_turn_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_player.png"), "Player Turn Order", player_dimension.getWidth(), player_dimension.getHeight());
		player_canal_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_canal_big.jpg"), "Player Canal", link_dimension.getWidth(), link_dimension.getHeight());
		player_rail_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_rail_big.jpg"), "Player Rail", link_dimension.getWidth(), link_dimension.getHeight());
		player_canal_img.showImage(link_location.getX(), link_location.getY());
		
		brass_tokens = new BrassTokens(p_id, color, brass_xml);
	}
	
	public String getCardName(int card_num)
	{
		return brass_hand.getCardName(card_num);
	}
	
	public int getCardCityTechID(int card_num)
	{
		return  brass_hand.getCardCityTechID(card_num);
	}
	
	public int getNumBrassCards()
	{
		return brass_hand.getNumCards();
	}
	
	public int getMoney()
	{
		return money;
	}
	
	public int getPlayerID()
	{
		return player_id;
	}
	
	public void showHand()
	{
		brass_hand.showHand();
	}
	
	public void addCardToHand(BrassCard brass_card)
	{
		brass_hand.addCardToHand(brass_card);
	}
	
	public void setTurnOrderImageLoc(int x, int y)
	{
		player_turn_img.showImage(x, y);
	}
	
	public void payForDemandTrack(int demand_track_cost)
	{
		money -= demand_track_cost;
		amount_spent += demand_track_cost;
	}
	
	public boolean canPlayerBuyFromDemandTrack(int demand_track_cost)
	{
		return money >= demand_track_cost;
	}
}
