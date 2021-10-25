package brass;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Comparator;

import java.awt.Graphics;
import java.awt.Color;
import java.awt.Image;

import gui.DrawImage;
import gui.DrawFont;
import gui.PixelPoint;
import gui.PixelDimension;
import gui.HotSpot;

import util.QueueLinked;

import pqsort.PQSort;

import pqsort.PQType;

class BrassPlayers
{
	private List<BrassPlayer> brass_players;
	private List<HotSpot> display_player_hot_spots;
	private List<PixelPoint> turn_order_locations;

	//private QueueLinked<BrassPlayer> turn_order;
	private List<BrassPlayer> turn_order;

	private int active_player_id;
	private int view_player_id;
	private int turn_count;
	private boolean is_first_turn;

	public void playerActionCompleted(BrassDeck brass_deck)
	{
		BrassPlayer current_player = brass_players.get(active_player_id - 1);

		if (!is_first_turn && current_player.getNumActionsTaken() < 2)
		{
			return;
		}

		current_player.discardCards(is_first_turn);

		if (!brass_deck.isDeckExhausted())
		{
			current_player.addCardToHand(brass_deck.deal());
			if (!is_first_turn)
			{
				current_player.addCardToHand(brass_deck.deal());
			}
		}

		current_player.showHand();

		turn_count++;

		if (turn_count == 5)  //all four players have taken a turn
		{
			is_first_turn = false;
			turn_count = 1;

			//DO THIS
			//sort the players by amount spent (ascending) using PQSort
			//use the BinarySearchTree implementation
			Iterator<BrassPlayer> check = turn_order.iterator();
			while(check.hasNext())
			{
				BrassPlayer player = check.next();
				System.out.println(player.getPlayerID());
			}
			PQType type = PQType.TREE;

			BrassCompareAmountSpent comp = new BrassCompareAmountSpent(true);
			this.turn_order = PQSort.pqSort(turn_order, comp, type);

			//DO THIS
			//bookkeeping iterator to set the turn order image location, reset amount spent, and receive income
			Iterator<BrassPlayer> turn_order_iter = turn_order.iterator();
			int count = 0;  //counter to access the turn order image location for each player

			while (turn_order_iter.hasNext())
			{
				BrassPlayer player = turn_order_iter.next();
				int id = player.getPlayerID();
				System.out.println(id);
				player.resetAmountSpent();

				player.receiveIncome();

				PixelPoint pixel = turn_order_locations.get(count);

				int x = pixel.getX();

				int y = pixel.getY();

				player.setTurnOrderImageLoc(x, y);

				count++;
			}


		}

		BrassPlayer next_player = turn_order.get(turn_count - 1);
		active_player_id = next_player.getPlayerID();
		view_player_id = active_player_id;
	}

	public int getMoney(int player_id)
   {
	   BrassPlayer brass_player = brass_players.get(player_id - 1);
	   return brass_player.getMoney();
   }

	public void payForLink(int link_cost, int player_id)
	{
		BrassPlayer brass_player = brass_players.get(player_id - 1);
		brass_player.payForLink(link_cost);
	}

	public boolean isTechLevelRequirementMet(int industry_id, int player_id, boolean brass_phase)
	{
		int phase = 1;
		if (brass_phase == true) phase = 2;  //rail phase

		BrassPlayer brass_player = brass_players.get(player_id - 1);
		return brass_player.isTechLevelRequirementMet(industry_id, phase);
	}

	public BrassToken payForToken(int industry_id, int player_id)
	{
		BrassPlayer brass_player = brass_players.get(player_id - 1);
		BrassToken brass_token = brass_player.payForToken(industry_id);
		return brass_token;
	}

	public boolean canPlayerAffordIndustry(int industry_id, int player_id)
	{
		BrassPlayer brass_player = brass_players.get(player_id - 1);
		return brass_player.canPlayerAffordIndustry(industry_id);
	}

	public int getSelectedToken(int x, int y)
	{
		BrassPlayer brass_player = brass_players.get(getActivePlayerID() - 1);
		return brass_player.getSelectedToken(x, y);
	}

	public void cancelCardSelection()
	{
		BrassPlayer current_player = brass_players.get(active_player_id - 1);
		current_player.cancelCardSelection();
	}

	public boolean isFirstTurn()
	{
		return is_first_turn;
	}

	public void selectCard(int card_num)
	{
		BrassPlayer brass_player = brass_players.get(getActivePlayerID() - 1);
		brass_player.selectCard(card_num);
	}

	public void executeLoanAction(int loan_amount, BrassTrack brass_track)
	{
		BrassPlayer brass_player = brass_players.get(getActivePlayerID() - 1);
		brass_player.executeLoanAction(loan_amount, brass_track);
	}

	public int getCardCityTechID(int brass_card_num)
	{
		BrassPlayer brass_player = brass_players.get(getActivePlayerID() - 1);
		return brass_player.getCardCityTechID(brass_card_num);
	}

	public int getSelectedCard(int x, int y)
	{
		BrassPlayer brass_player = brass_players.get(getActivePlayerID() - 1);
		return brass_player.getSelectedCard(x, y);
	}

	/*
	public void changePhase()
	{
		Iterator<BrassPlayer> brass_player_iter = brass_players.iterator();
		while(brass_player_iter.hasNext())
		{
			BrassPlayer brass_player = brass_player_iter.next();
			brass_player.changePhase();
		}
	}
	*/
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
		util.Permutation p = util.PermutationFactory.getPermutation("resources/brass_turn_order.txt", 4, 4);

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

		turn_order = new ArrayList<BrassPlayer>();
		int count = 1;
		while(p.hasNext())
		{
			Integer i = p.next();
			BrassPlayer brass_player = brass_players.get(i - 1);
			turn_order.add(brass_player);
			brass_player.setTurnOrderImageLoc(turn_order_locations.get(count-1).getX(),turn_order_locations.get(count-1).getY());
			count++;
		}

		//4 players, each player receives eight cards
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				BrassPlayer brass_player = turn_order.get(j - 1);
				brass_player.addCardToHand(brass_deck.deal());
			}
		}

		for (int i = 0; i < 4; i++)
		{
			BrassPlayer brass_player = brass_players.get(i);
			brass_player.showHand();
		}

		//get the starting player's id
		BrassPlayer start_player = turn_order.get(0);
		active_player_id = start_player.getPlayerID();
		//turn_order.enqueue(start_player);

		view_player_id = active_player_id;
		turn_count = 1;
		is_first_turn = true;
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
}
