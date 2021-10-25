package brass;

import java.awt.Graphics;

import gui.PixelPoint;
import gui.PixelDimension;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

class BrassHand
{
	private List<BrassCard> brass_hand;
	
	private List<PixelPoint> small_card_centers;
	private List<PixelPoint> big_card_centers;
	
	public void validCardSelected(int card_id)
	{
		BrassCard brass_card = brass_hand.get(card_id - 1);
		brass_card.validCardSelected(card_id);
	}
	
	public int getSelectedCard(int x, int y)
	{
		Iterator<BrassCard> card_iter = brass_hand.iterator();
		int count = 1;
		while(card_iter.hasNext())
		{
			BrassCard brass_card = card_iter.next();
			if (brass_card.isCardSelected(x, y))
			{
				return count;
			}
			count++;
		}
		return 0;  //a card was not selected
	}
	
	public void draw(Graphics g)
	{
		Iterator<BrassCard> card_iter = brass_hand.iterator();
		while(card_iter.hasNext())
		{
			BrassCard brass_card = card_iter.next();
			brass_card.draw(g);
		}
	}
	
	public BrassHand(BrassXML brass_xml)
	{
		brass_hand = new ArrayList<BrassCard>();
		
		small_card_centers = brass_xml.getPixelCenters("small_cards");
		big_card_centers = brass_xml.getPixelCenters("big_cards");
	}
	
	public String getCardName(int card_num)
	{
		BrassCard brass_card = brass_hand.get(card_num - 1);
		return  brass_card.getCardName();
	}
	
	public int getCardCityTechID(int card_num)
	{
		BrassCard brass_card = brass_hand.get(card_num - 1);
		return  brass_card.getCardCityTechID();
	}
	
	public int getNumCards()
	{
		return brass_hand.size();
	}
	
	public void showHand()
	{
		assignAllSmallCardLocations();
	}
	
	//the hand size should not be greater than 8, but can be less than 8 if the draw deck is empty
	public void addCardToHand(BrassCard brass_card)
	{
		brass_hand.add(brass_card);
	}
	
	public void assignAllSmallCardLocations()
	{
		int small_card_count = 1;
		Iterator<BrassCard> card_iter = brass_hand.iterator();
		while(card_iter.hasNext())
		{
			BrassCard brass_card = card_iter.next();
			//skip index 0 as it is for the card back
			PixelPoint small_card_center = small_card_centers.get(small_card_count);
			brass_card.showSmallCard(small_card_center.getX(), small_card_center.getY());
			small_card_count++;
		}
	}
}
