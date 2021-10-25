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
	
	private DrawImage player_turn_img;
	
	private DrawImage player_canal_img;
	private DrawImage player_rail_img;
	
	private DrawImage player_income_img;
	private DrawImage player_victory_img;
	
	private int income_index;
	private int victory_index;
	
	public void payForLink(int link_cost)
	{
		//lab 8 assert
		assert money >= link_cost : "Player cannot afford link.";
		money -= link_cost;
		amount_spent += link_cost;
	}
	
	public boolean isTechLevelRequirementMet(int industry_id, int brass_phase)
	{
		return brass_tokens.isTechLevelRequirementMet(industry_id, brass_phase);
	}
	
	public void receiveIncome()
	{
		money += BrassTrack.getIncomeAmount(income_index);
	}
	
	public void resetAmountSpent()
	{
		amount_spent = 0;
	}
	
	public int getAmountSpent()
	{
		return amount_spent;
	}
	
	public BrassToken payForToken(int industry_id)
	{
		//assert that the player has enough money to build the token
		BrassToken brass_token = brass_tokens.removeTokenFromPlayer(industry_id);
		int token_cost = brass_token.getTokenCost();
		
		//assert for lab 8
		assert (money >= token_cost) : "Player does not have enough money to build the industry.";
		
		money -= token_cost;
		amount_spent += token_cost;
		return brass_token;
	}
	
	public boolean canPlayerAffordIndustry(int industry_id)
	{
		return brass_tokens.canPlayerAffordIndustry(industry_id, money);
	}
	
	public int getSelectedToken(int x, int y)
	{
		return brass_tokens.getSelectedToken(x, y);
	}
	
	public int getNumActionsTaken()
	{
		return brass_hand.getNumActionsTaken();
	}
	
	public void executeLoanAction(int loan_amount, BrassTrack brass_track)
	{
		money += loan_amount;
		income_index = BrassTrack.takeLoan(income_index, loan_amount);
		updateTrackMarkers(brass_track);
	}
	
	public void selectCard(int card_num)
	{
		brass_hand.selectCard(card_num);
	}
	
	public void cancelCardSelection()
	{
		brass_hand.cancelCardSelection();
	}
	
	public void discardCards(boolean first_turn)
	{
		brass_hand.discardCards(first_turn);
	}
	
	public void changePhase()
	{
		player_canal_img.hideImage();
		
		int rail_x = player_canal_img.getXCenter();
		int rail_y = player_canal_img.getYCenter();
		
		player_rail_img.showImage(rail_x, rail_y);
	}
	
	public void updateTrackMarkers(BrassTrack brass_track)
	{
		int income_x = brass_track.getXPixel(income_index);
		int income_y = brass_track.getYPixel(income_index);
		player_income_img.showImage(income_x, income_y);
		
		if (victory_index > 100) victory_index = victory_index - 100;
		int victory_x = brass_track.getXPixel(victory_index);
		int victory_y = brass_track.getYPixel(victory_index);
		player_victory_img.showImage(victory_x, victory_y);
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
	
	public void setTurnOrderImageLoc(int x, int y)
	{
		player_turn_img.showImage(x, y);
	}
	
	public void validCardSelected(int card_id)
	{
		brass_hand.validCardSelected(card_id);
	}
	
	public int getSelectedCard(int x, int y)
	{
		return brass_hand.getSelectedCard(x, y);
	}
	
	public void draw(Graphics g, int active_player_id, int view_player_id)
	{
		if (active_player_id == player_id)
		{
			brass_hand.draw(g);
			
			//only one of the following two images will actually be drawn
			player_canal_img.draw(g);
			player_rail_img.draw(g);
		}
		
		if (amount_spent < 10)
		{
			verdana_bold_amount_spent.draw(g, " " + amount_spent + "");
		}
		else
		{
			verdana_bold_amount_spent.draw(g, amount_spent + "");
		}
		
		player_turn_img.draw(g);
		
		if (player_id == view_player_id)
		{
			player_income_img.draw(g);
			player_victory_img.draw(g);
			brass_tokens.draw(g);
			
			if (money < 10)
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
	public BrassPlayer(int p_id, BrassXML brass_xml, String color, PixelPoint amount_spent_loc, BrassTrack brass_track)
	{
		gui.ImageLoader il = gui.ImageLoader.getImageLoader();
		
		income_index = 10;
		victory_index = 0;
		
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
		PixelDimension hat_dimension = brass_xml.getPixelDimension("hat");
		
		player_turn_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_player.png"), "Player Turn Order", player_dimension.getWidth(), player_dimension.getHeight());
		player_canal_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_canal_big.jpg"), "Player Canal", link_dimension.getWidth(), link_dimension.getHeight());
		player_rail_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_rail_big.jpg"), "Player Rail", link_dimension.getWidth(), link_dimension.getHeight());
		player_canal_img.showImage(link_location.getX(), link_location.getY());
		
		player_income_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_player.png"), "Player Income Marker", player_dimension.getWidth(), player_dimension.getHeight());
		player_victory_img = new DrawImage(il.getImage("images/" + color + "/" + color + "_hat.jpg"), "Player Victory Point Marker", hat_dimension.getWidth(), hat_dimension.getHeight());
		
		updateTrackMarkers(brass_track);
		
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
}
