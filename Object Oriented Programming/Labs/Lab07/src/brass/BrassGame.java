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
	
	private BrassState select_card_state;
	private BrassState select_action_state;
	private BrassState link_action_state;
	
	private BrassState current_state;
	
	//DO THIS
	//delegate mouse clicks to the current_state (mouseClicked)
	public void mouseClicked(int x_click, int y_click)
	{
		current_state.mouseClicked(x_click, y_click);
	}
	
	//DO THIS
	//update current_state to brass_state
	public void changeState(BrassState brass_state)
	{
		current_state = brass_state;
	}
	
	public BrassState getSelectCardState()
	{
		return select_card_state;
	}
	
	public BrassState getSelectActionState()
	{
		return select_action_state;
	}
	
	public BrassState getLinkActionState()
	{
		return link_action_state;
	}
	
	//DO THIS
	//make sure that the link has not already been constructed
	//make sure that the player has enough money to build the link
	public boolean canBuildLink(int link_id, int player_id)
	{
		//check if the link is constructed in brass_board
		//  return false if it is not constructed
		
		if (brass_board.isLinkConstructed(link_id))
		{
			return false;
		}
		
		//get the correct link_cost depending on the brass_phase
		
		int link_cost;

		if (brass_phase)
		{
			link_cost = BrassLinkCostEnum.RAIL.getValue();
		}
		else
		{
			link_cost = BrassLinkCostEnum.CANAL.getValue();
		}
		
		//check if the player_id has enough money to build the link
		//you can call getMoney() on brass_players
		//if the player_id has enough money to cover the link_cost
		//  then return true, otherwise false
		
		int money = brass_players.getMoney(player_id);

		if (money >= link_cost)
		{
			return true;
		}

		return false;
	}
	
	//DO THIS
	//assume that it is okay to build the link
	//the player needs to pay for the link
	//the board needs to build the link
	public void buildLink(int link_id, int player_id)
	{
		//get the link_cost depending on brass_phase
		
		int link_cost;

		if (brass_phase)
		{
			link_cost = BrassLinkCostEnum.RAIL.getValue();
		}
		else
		{
			link_cost = BrassLinkCostEnum.CANAL.getValue();
		}
		
		//make the player_id pay for link using brass_players
		
		brass_players.payForLink(link_cost, player_id);
		
		//buildLink on brass_board
		
		brass_board.buildLink(link_id, player_id);
		
	}
	
	public BrassGame()
   {
	   //DO THIS
	   //  pass 'this' as a parameter to the constructors below
	   //NOTE to remember for the exam: remember that 'this' points to the current instance of the class which is a BrassGame object
	   select_card_state = new BrassSelectCardState(this);
	   select_action_state = new BrassSelectActionState(this);
	   link_action_state = new BrassLinkActionState(this);
	   current_state = select_card_state;
	   
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
	
	public int getSelectedLink(int x, int y)
	{
		return brass_board.getSelectedLink(x, y);
	}
	
	public boolean getBrassPhase()
	{
		return brass_phase;
	}
	
	public int getActivePlayerID()
	{
		return brass_players.getActivePlayerID();
	}
	
	public int getSelectedPlayer(int x, int y)
	{
		return brass_players.getSelectedPlayer(x, y);
	}

	public void displayPlayer(int display_player_id)
	{
		brass_players.displayPlayer(display_player_id);
	}
	
	public void cancelCardSelection()
	{
		brass_players.cancelCardSelection();
	}
	
	public void playerActionCompleted()
	{
		brass_players.playerActionCompleted(brass_deck);
	}
	
	public void selectCard(int card_num)
	{
		brass_players.selectCard(card_num);
	}
	
	public void loanActionSelected(int loan_amount)
	{
		brass_players.executeLoanAction(loan_amount, brass_track);
	}
	
	public int getSelectedAction(int x, int y)
	{
		return brass_board.getSelectedAction(x, y);
	}
	
	public int getCardCityTechID(int brass_card_num)
	{
		return brass_players.getCardCityTechID(brass_card_num);
	}
	
	public int getSelectedCard(int x, int y)
	{
		return brass_players.getSelectedCard(x, y);
	}
   
   public void draw(Graphics g, int width, int height)
   {
		brass_board.draw(g);
		brass_players.draw(g);
		brass_deck.draw(g);
   }
   
   public void keyPressed(char key) 
	{
		System.out.println("The " + key + " key was pressed.");
	}
}
