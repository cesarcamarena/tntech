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

import util.QueueLinked;

class BrassPlayers
{
	private List<BrassPlayer> brass_players;
	private List<HotSpot> display_player_hot_spots;
	private List<PixelPoint> turn_order_locations;
	
	private QueueLinked<BrassPlayer> turn_order;
	
	private int active_player_id;
	private int view_player_id;
	
	public int getActivePlayerID()
	{
		return active_player_id;
	}
	
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
	
	public int getSelectedCard(int player_id, int x, int y)
	{
		BrassPlayer brass_player = brass_players.get(player_id - 1);
		return brass_player.getSelectedCard(x, y);
	}
	
	public BrassPlayers(BrassDeck brass_deck, BrassXML brass_xml, BrassTrack brass_track)
	{
		brass_players = new ArrayList<BrassPlayer>();
		util.Permutation fp = util.PermutationFactory.getPermutation("resources/brass_turn_order.txt", 4, 4);
		
		List<PixelPoint> amount_spent_centers = brass_xml.getPixelCenters("amount_spent");
		BrassPlayer red = new BrassPlayer(1, brass_xml, "red", amount_spent_centers.get(0), brass_track);
		brass_players.add(red);
		BrassPlayer purple = new BrassPlayer(2, brass_xml, "purple", amount_spent_centers.get(1), brass_track);
		brass_players.add(purple);
		BrassPlayer green = new BrassPlayer(3, brass_xml, "green", amount_spent_centers.get(2), brass_track);
		brass_players.add(green);
		BrassPlayer yellow = new BrassPlayer(4, brass_xml, "yellow", amount_spent_centers.get(3), brass_track);
		brass_players.add(yellow);
		
		PixelDimension display_player_dimension = brass_xml.getPixelDimension("amount_spent");
		display_player_hot_spots = new ArrayList<HotSpot>();
		for (int i = 1; i <= 4; i++)
		{
			PixelPoint player_center = amount_spent_centers.get(i-1);
			HotSpot display_player_hot_spot = new HotSpot(i, player_center.getX() + 25, player_center.getY() - 15, display_player_dimension.getWidth(), display_player_dimension.getHeight());
			display_player_hot_spots.add(display_player_hot_spot);
		}
		
		turn_order_locations = brass_xml.getPixelCenters("turn_order");
		
		turn_order = new QueueLinked<BrassPlayer>();
		int count = 1;
		while(fp.hasNext())
		{
			Integer i = fp.next();
			BrassPlayer brass_player = brass_players.get(i - 1);
			turn_order.enqueue(brass_player);
			brass_player.setTurnOrderImageLoc(turn_order_locations.get(count-1).getX(),turn_order_locations.get(count-1).getY());
			count++;
		}
		
		//4 players, each player receives eight cards
		for (int i = 1; i <= 32; i++)
		{
			BrassPlayer brass_player = turn_order.dequeue();
			brass_player.addCardToHand(brass_deck.deal());
			turn_order.enqueue(brass_player);
		}
		
		for (int i = 1; i <= 4; i++)
		{
			BrassPlayer brass_player = brass_players.get(i-1);
			brass_player.showHand();
		}
		
		//get the starting player's id
		BrassPlayer start_player = turn_order.dequeue();
		active_player_id = start_player.getPlayerID();
		turn_order.enqueue(start_player);
		
		view_player_id = active_player_id;
	}
	
	public void advanceTurn(int clicked_card)
	{
		BrassPlayer current_player = brass_players.get(active_player_id - 1);
		current_player.validCardSelected(clicked_card); //print out the card name
		BrassPlayer next_player = turn_order.dequeue();
		active_player_id = next_player.getPlayerID();
		view_player_id = active_player_id;
		turn_order.enqueue(next_player);
	}
	
	public void draw(Graphics g)
   {	
		Iterator<BrassPlayer> player_iter = brass_players.iterator();
		while(player_iter.hasNext())
		{
			BrassPlayer brass_player = player_iter.next();
			brass_player.draw(g, active_player_id, view_player_id);
		}
   }
   
   public void payForDemandTrack(int demand_track_cost, int player_id)
	{
		BrassPlayer brass_player = brass_players.get(player_id - 1);
		brass_player.payForDemandTrack(demand_track_cost);
	}
	
	public boolean canPlayerBuyFromDemandTrack(int demand_track_cost, int player_id)
	{
		BrassPlayer brass_player = brass_players.get(player_id - 1);
		return brass_player.canPlayerBuyFromDemandTrack(demand_track_cost);
	}
}
