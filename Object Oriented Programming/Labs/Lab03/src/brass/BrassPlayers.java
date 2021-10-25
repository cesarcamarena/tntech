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
import gui.HotSpot;

class BrassPlayers
{
	//DO THIS
	//need an ArrayList of BrassPlayer (call it brass_players)

	private ArrayList<BrassPlayer> brass_players;
	
	
	private int active_player_id;
	private int view_player_id;  //can be different from active player id
	
	private List<HotSpot> display_player_hot_spots;  //amount spent hot spots
	
	//call the following methods from BrassGame when the mouse is clicked
	//in the amount spent box for a particular player
	public int getSelectedPlayer(int x, int y)
	{
		Iterator<HotSpot> display_player_iter = display_player_hot_spots.iterator();
		int count = 1;
		int selected_player = 0;
		while(display_player_iter.hasNext())
		{
			HotSpot display_player_spot = display_player_iter.next();
			if (display_player_spot.isSelected(x, y))
			{
				selected_player = count;
			}
			count++;
		}
		
		return selected_player;
	}
	
	public void displayPlayer(int selected_player_id)
	{
		view_player_id = selected_player_id;
	}
	
	public void nextPlayer()
	{
		//DO THIS
		//increment active player, reset view player to active player
		
		if (active_player_id >= 4)
		{
			active_player_id = 1;
		}
		else
		{
			active_player_id++;
		}
		
		view_player_id = active_player_id;
	}
	
	public BrassPlayers(BrassDeck brass_deck, BrassXML brass_xml)
	{
		//set up the hot spots in the amount spent areas
		List<PixelPoint> amount_spent_centers = brass_xml.getPixelCenters("amount_spent");
		PixelDimension display_player_dimension = brass_xml.getPixelDimension("amount_spent");
		display_player_hot_spots = new ArrayList<HotSpot>();
		for (int i = 1; i <= 4; i++)
		{
			PixelPoint player_center = amount_spent_centers.get(i-1);
			HotSpot display_player_hot_spot = new HotSpot(i, player_center.getX() + 25, player_center.getY() - 15, display_player_dimension.getWidth(), display_player_dimension.getHeight());
			display_player_hot_spots.add(display_player_hot_spot);
		}
		
		//DO THIS
		brass_players = new ArrayList<BrassPlayer>();
		
		//create the players and indicate where the amount spent text is located for each player
		BrassPlayer red = new BrassPlayer(1, brass_xml, "red", amount_spent_centers.get(0));
		brass_players.add(red);
		BrassPlayer purple = new BrassPlayer(2, brass_xml, "purple", amount_spent_centers.get(1));
		brass_players.add(purple);
		BrassPlayer green = new BrassPlayer(3, brass_xml, "green", amount_spent_centers.get(2));
		brass_players.add(green);
		BrassPlayer yellow = new BrassPlayer(4, brass_xml, "yellow", amount_spent_centers.get(3));
		brass_players.add(yellow);
		
		//DO THIS
		//deal eight cards to each player, cycling around all four players
		for (int i = 1; i <= 32; i++)  //i - 32
		{
			BrassCard bc = brass_deck.deal();
			
			if (i > 4)
			{
				BrassPlayer bp = brass_players.get(i%4);
				
				bp.addCardToHand(bc);
			}
			
			else
			{
				BrassPlayer bp = brass_players.get(i - 1);
				
				bp.addCardToHand(bc);
			}
			
			
		}
		
		//DO THIS
		//assign the small card locations to each players' hand
		//refer to BrassHand for the method to call on each player
		for (int i = 1; i <= 4; i++)
		{
			BrassPlayer bp = brass_players.get(i - 1);
			
			bp.showHand();
	
		}
		
		//DO THIS
		//initialize these
		active_player_id = 1;
		view_player_id = 1;
	}
	
	public void draw(Graphics g)
   {	
		//DO THIS
		//use a for loop to draw each of the BrassPlayer objects
		
		for (int i = 1; i <= 4; i++)
		{
			BrassPlayer bp = brass_players.get(i - 1);
			
			bp.draw(g, active_player_id, view_player_id);
		}
		
		
		
		
		
   }
}
