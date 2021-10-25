package brass;

import java.awt.Graphics;

import gui.PixelPoint;
import gui.PixelDimension;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

class BrassHand
{
	//declare an ArrayList to store all of the BrassCards that make up this BrassHand (call it brass_hand)
	
	private List<PixelPoint> small_card_centers;
	private List<PixelPoint> big_card_centers;
	
	private ArrayList<BrassCard> brass_hand;
	
	//constructor
	public BrassHand(BrassXML brass_xml)
	{
		//create the brass_hand
		brass_hand = new ArrayList<BrassCard>();

		//look at BrassXML methods to obtain the card centers
		//the element names are "small_cards" and "big_cards"
		small_card_centers = brass_xml.getPixelCenters("small_cards");
		big_card_centers = brass_xml.getPixelCenters("big_cards");
	}
	
	public String getCardName(int card_num)
	{
		//DO THIS (remember that ArrayList is 0-based)
		BrassCard bc = brass_hand.get(card_num - 1);
		
		return bc.getCardName();
	}
	
	public int getCardCityTechID(int card_num)
	{
		//DO THIS
		BrassCard bc = brass_hand.get(card_num - 1);
		
		return bc.getCardCityTechID();
	}
	
	public int getNumCards()
	{
		//DO THIS
		return brass_hand.size();
	}
	
	public void addCardToHand(BrassCard brass_card)
	{
		//DO THIS (add the BrassCard to the BrassHand)
		brass_hand.add(brass_card);
	}
	
	public void showHand()
	{
		assignAllSmallCardLocations();
	}
	
	public void assignAllSmallCardLocations()
	{
		//DO THIS
		//when a player's hand is to be displayed, the locations of the small cards must be assigned
		//loop over the player's cards and assign their locations using the small_card_centers list
		//you may need to look at the methods in BrassCard (showSmallCard)
		
		//skip index 0 in the small_card_centers list (but not brass_hand)
		//index 0 is the location for showing the back of the card, not needed here
		
		for (int i = 0; i < brass_hand.size(); i++)
		{
			BrassCard bc = brass_hand.get(i);
			
			PixelPoint pp = small_card_centers.get(i + 1);
			
			bc.showSmallCard(pp.getX(), pp.getY());
		}
		
		
		
		
	}
	
	public void draw(Graphics g)
	{
		//DO THIS
		//use a for loop to visit each card in the hand
		
		for (int i = 0; i < brass_hand.size(); i++)
		{
			BrassCard bc = brass_hand.get(i);
			bc.draw(g);
		}

		
		
		//brass_card.draw(g);  //tell the card to draw itself

	}
}

//Cesar Camarena    cacamarena42@students.tntech.edu    615  686  5513
//Robert Broadhead  rkbroadhea@students.tntech.edu      615  585  9617