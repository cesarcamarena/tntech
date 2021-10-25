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
	//declare a BrassHand (call it brass_hand)
	private BrassHand brass_hand;
	
	//declare BrassTokens (call it brass_tokens)
	private BrassTokens brass_tokens;
	
	//other items that the BrassPlayer need to keep track of
	private int player_id;
	private int amount_spent;
	private int money;
	
	//needed to display the money and the amount spent
	private DrawFont verdana_bold_amount_spent;
	private DrawFont verdana_bold_money;
	
	private DrawImage player_canal_img;
	private DrawImage player_rail_img;
	
	//card_num is an integer between 1 and 8 and indicates which card in the player's hand is requested
	public String getCardName(int card_num)
	{
		//DO THIS
		return brass_hand.getCardName(card_num);
	}
	
	public int getCardCityTechID(int card_num)
	{
		//DO THIS
		return brass_hand.getCardCityTechID(card_num);
	}
	
	public int getNumCards()
	{
		//DO THIS
		return brass_hand.getNumCards();
	}
	
	public int getMoney()
	{
		//DO THIS
		return money;
	}
	
	public int getPlayerID()
	{
		//DO THIS
		return player_id;
	}
	
	public void showHand()
	{
		//DO THIS
		brass_hand.showHand();
	}
	
	public void addCardToHand(BrassCard brass_card)
	{
		//DO THIS
		brass_hand.addCardToHand(brass_card);
	}
	
	//1 = red, 2 = purple, 3 = green, 4 = yellow
	public BrassPlayer(int p_id, BrassXML brass_xml, String color, PixelPoint amount_spent_loc)
	{
		gui.ImageLoader il = gui.ImageLoader.getImageLoader();

		player_id = p_id;
		amount_spent = 0;
		money = 30;
		
		//DO THIS
		brass_hand = new BrassHand(brass_xml);
		
		PixelPoint money_loc = brass_xml.getPixelCenter("money");
		int money_size = brass_xml.getTextSize("money");
		int amount_spent_size = brass_xml.getTextSize("amount_spent");
		
		verdana_bold_money = new DrawFont("Verdana", "bold", money_size, new Color(0,0,0), money_loc.getX(), money_loc.getY());
		verdana_bold_amount_spent = new DrawFont("Verdana", "bold", amount_spent_size, new Color(0,0,0), amount_spent_loc.getX(), amount_spent_loc.getY());
		
		PixelDimension link_dimension = brass_xml.getPixelDimension("link");
		PixelPoint link_location = brass_xml.getPixelCenter("link");
		
		player_canal_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_canal_big.jpg"), "Player Canal", link_dimension.getWidth(), link_dimension.getHeight());
		player_rail_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_rail_big.jpg"), "Player Rail", link_dimension.getWidth(), link_dimension.getHeight());
		player_canal_img.showImage(link_location.getX(), link_location.getY());
		
		//DO THIS
		//look at BrassTokens constructor
		brass_tokens = new BrassTokens(p_id, color, brass_xml);
	}
	
	//DO THIS
	//will need to pass active_player_id and view_player_id to this method to only show the active player's cards
	public void draw(Graphics g, int active_player_id, int view_player_id)
	{
		if (player_id == active_player_id)
		{
			brass_hand.draw(g);  //only active player's hand should ever be displayed
		}
		
		if (player_id == view_player_id)
		{
			brass_tokens.draw(g);  //draw the view player's tokens
		}
		
		//only one of the following two images will actually be drawn
		if (player_id == active_player_id)
		{
			player_canal_img.draw(g);
		}
		
		else
		{
			player_rail_img.draw(g);
		}
		
		
		if (player_id == view_player_id)
		{
			if (money < 10)  //draw the view player's money
			{
				verdana_bold_money.draw(g, " " + money + "");
			}
			
			else
			{
				verdana_bold_money.draw(g, money + "");
			}
		}
		
		if (amount_spent < 10)  //draw everyone's amount spent
		{
			verdana_bold_amount_spent.draw(g, " " + amount_spent + "");
		}
		else
		{
			verdana_bold_amount_spent.draw(g, amount_spent + "");
		}
	}
}
