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
	private BrassTrack brass_track;
	
	private boolean brass_phase;
   
   public BrassGame()
   {
	   brass_phase = false;  //canal_phase
	   
		gui.ImageLoader il = gui.ImageLoader.getImageLoader();
		BrassXML brass_xml = new BrassXML("resources/brass_pixels.xml");
		
		brass_deck = new BrassDeck(il, brass_xml);
		brass_deck.dealStartCanalPhase();
		
		brass_track = new BrassTrack(brass_xml);
		
		brass_players = new BrassPlayers(brass_deck, brass_xml, brass_track);
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
			return;
		}
		
		int active_player_id = brass_players.getActivePlayerID();
		int clicked_card = brass_players.getSelectedCard(active_player_id, x_click, y_click);

		if (clicked_card > 0)
		{
			brass_players.advanceTurn(clicked_card);
			int demand_track_cost = brass_board.getCostToBuyFromIronDemandTrack();
			System.out.println(demand_track_cost);
			if (brass_players.canPlayerBuyFromDemandTrack(demand_track_cost, active_player_id))
			{
				brass_board.buyFromIronDemandTrack();
				brass_players.payForDemandTrack(demand_track_cost, active_player_id);
			}
			return;
		}
		
		
		//DO THIS
		//respond to connection requests (build connections and change phase)
		
		if (brass_board.isChangePhaseSelected(x_click, y_click))
		{
			brass_players.changePhase();

			brass_phase = true;
			//brass_phase = brass_board.getBrassPhase();
		}
		
		int selected_link = brass_board.getSelectedLink(x_click, y_click);

		if (selected_link != 0)
		{
			if (brass_players.canPayForLink(brass_phase, active_player_id))
			{
				brass_players.payForLink(brass_phase, active_player_id);

				brass_board.constructLink(selected_link, active_player_id);
			}
		}		
		
		
		
		System.out.println("The mouse was clicked at (" + x_click + "," + y_click + ").");
	}
   
   public void keyPressed(char key) 
	{
		System.out.println("The " + key + " key was pressed.");
	}
}
