package brass;

import java.awt.Graphics;
import java.util.List;
import java.util.ArrayList;

import gui.BasicGUI;
import gui.DrawImage;
import gui.Drawable;
import gui.PixelPoint;
import gui.PixelDimension;

public class BrassGame implements Drawable
{
	private DrawImage board_img;
	private BasicGUI brass_gui;
	private BrassDeck brass_deck;
	private BrassPlayers brass_players;
	private BrassBoard brass_board;
   
   public BrassGame()
   {
		gui.ImageLoader il = gui.ImageLoader.getImageLoader();
		BrassXML brass_xml = new BrassXML("resources/brass_pixels.xml");
		
		brass_deck = new BrassDeck(il, brass_xml);
		brass_deck.dealStartCanalPhase();
		
		brass_players = new BrassPlayers(brass_deck, brass_xml);
		brass_board = new BrassBoard(brass_xml);
		
		//create the gui last
		PixelDimension gui_dimension = brass_xml.getPixelDimension("gui");
		brass_gui = new BasicGUI(gui_dimension.getWidth(), gui_dimension.getHeight(), "Brass", "images/brass_icon.png", this);
   }
   
   public void draw(Graphics g, int width, int height)
   {
		brass_board.draw(g);
		brass_players.draw(g);
		brass_deck.draw(g);
   }
   
   public void mouseClicked(int x_click, int y_click)
	{
		int display_player_id = brass_players.getSelectedPlayer(x_click, y_click);
		if (display_player_id > 0)
		{
			brass_players.displayPlayer(display_player_id); 
		}
		
		
		//DO THIS
		//determine if a card was clicked on
		//if so, advance the turn
		
		else
		{
			int selectedCard = brass_players.getSelectedCard(x_click, y_click, display_player_id);
			
			if (selectedCard > 0)
			{
				int active_player_id = brass_players.getActivePlayerID();

				int demand_track_cost = brass_board.getCostToBuyFromIronDemandTrack();

				if (brass_players.canPlayerBuyFromDemandTrack(demand_track_cost, active_player_id))
				{
					brass_board.buyFromIronDemandTrack();
					brass_players.payForDemandTrack(demand_track_cost, active_player_id);
				}

				brass_players.advanceTurn(selectedCard);
			}

		}
		
		
		
		
		
		
		
		//uncomment these lines when working on the Brass Demand Track
		//player purchases from the demand track when a card is clicked on
		
		
		System.out.println("The mouse was clicked at (" + x_click + "," + y_click + ").");
	}
   
   public void keyPressed(char key) 
	{
		System.out.println("The " + key + " key was pressed.");
	}
}
