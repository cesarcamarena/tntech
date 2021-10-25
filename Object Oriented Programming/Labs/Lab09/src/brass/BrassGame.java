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
	private BrassState build_action_state;
	
	private BrassState current_state;
	
	public boolean canBuildLink(int link_id, int player_id)
	{
		//has the link already been constructed?
		if (brass_board.isLinkConstructed(link_id)) 
		{
			return false;
		}
		
		int link_cost = BrassLinkCostEnum.CANAL.getValue();
		if (brass_phase) link_cost = BrassLinkCostEnum.RAIL.getValue();

		int coal_city_id = 0;  //no coal required for links in the canal phase

		int player_money = brass_players.getMoney(player_id);
		boolean can_pay_for_link = (player_money >= link_cost);
		//check for connection to player network
		boolean is_link_connected_to_player_network = brass_board.isLinkConnectedToPlayerNetwork(link_id, player_id);
		
		return (coal_city_id >= 0) && can_pay_for_link && is_link_connected_to_player_network;
	}
	
	public void buildLink(int link_id, int player_id)
	{
		int coal_city_id = 0;  //no coal is required in canal phase
		int link_cost;
		if (!brass_phase)
		{
			link_cost = BrassLinkCostEnum.CANAL.getValue();
		}
		else
		{
			link_cost = BrassLinkCostEnum.RAIL.getValue();
		}
		brass_players.payForLink(link_cost, player_id);
		brass_board.buildLink(0, link_id, player_id, brass_players, brass_track);
	}
	
	public void buildIndustry(int city_id, int industry_id, int player_id)
	{
		//place asserts in locations indicated by the method calls below
		//to make sure that the build is okay
		//not everything can be checked, however
		BrassToken brass_token = brass_players.payForToken(industry_id, player_id);
		brass_board.placeTokenInCity(city_id, brass_token);
	}
	
	public int getNumTokensOnBoard(int player_id)
	{
		return brass_board.getNumTokensOnBoard(player_id);
	}
	
	public int getNumTokensInCity(int city_id, int player_id)
	{
		return brass_board.getNumTokensInCity(city_id, player_id);
	}
	
	public boolean canPlayerAffordIndustry(int industry_id, int player_id)
	{
		return brass_players.canPlayerAffordIndustry(industry_id, player_id);
	}
	
	public boolean canCityAcceptToken(int city_id, int industry_id)
	{
		return brass_board.canCityAcceptToken(city_id, industry_id);
	}
	
	public int getSelectedToken(int x, int y)
	{
		return brass_players.getSelectedToken(x, y);
	}
	
	public int getSelectedCity(int x, int y)
	{
		return brass_board.getSelectedCity(x, y);
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
	
	public boolean canBuildIndustry(boolean city_card, int city_id, int industry_id, int player_id)
	{	
		//can assert the next two conditions if the protocol is not followed
		//but the subsequent statements there is no easy way to assert
		boolean can_city_accept = canCityAcceptToken(city_id, industry_id); //can that industry be placed in the city
		boolean can_player_afford = canPlayerAffordIndustry(industry_id, player_id); //does the player have enough money
		
		int num_tokens_in_city = getNumTokensInCity(city_id, player_id);
		int num_tokens_on_board = getNumTokensOnBoard(player_id);
		
		//can't really assert the following checks if the protocol is not followed
		//in the canal phase, players can only have one token in a city
		boolean can_player_place_in_city = (num_tokens_in_city == 0 || brass_phase);
		//players can use industry cards similar to city cards if they have no tokens on the board
		boolean is_connected_to_network = brass_board.isCityConnectedToPlayerNetwork(city_id, player_id);
		boolean can_player_use_industry_card = (city_card || (num_tokens_on_board == 0) || is_connected_to_network);
		boolean is_tech_level_requirement_met = brass_players.isTechLevelRequirementMet(industry_id, player_id, brass_phase);
		return can_city_accept && can_player_afford && can_player_place_in_city && can_player_use_industry_card && is_tech_level_requirement_met;
	}
	
	public BrassGame(int num_players)
	{
		this();
		System.out.println("num_players: " + num_players);
	}
   
   public BrassGame()
   {
	   BrassXML brass_xml = new BrassXML("resources/brass_pixels.xml");
	   
	   select_card_state = new BrassSelectCardState(this);
	   select_action_state = new BrassSelectActionState(this);
	   link_action_state = new BrassLinkActionState(this);
	   build_action_state = new BrassBuildActionState(this);
	   current_state = select_card_state;
	   
	   brass_phase = false;  //canal_phase
	   
		gui.ImageLoader il = gui.ImageLoader.getImageLoader();
		
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
		current_state.mouseClicked(x_click, y_click);
	}
	
	public BrassState getSelectCardState()
	{
		return select_card_state;
	}
	
	public BrassState getSelectActionState()
	{
		return select_action_state;
	}
	
	public BrassState getBuildActionState()
	{
		return build_action_state;
	}
	
	public BrassState getLinkActionState()
	{
		return link_action_state;
	}
	
	public void changeState(BrassState brass_state)
	{
		current_state = brass_state;
	}
   
   public void keyPressed(char key) 
	{
		System.out.println("The " + key + " key was pressed.");
	}
	
	public int[] getScreenDimensions()
	{
		return brass_gui.getScreenDimensions();
	}
	
	public int getGUIWidth()
	{
		return brass_gui.getWidth();
	}
	
	public int getGUIHeight()
	{
		return brass_gui.getHeight();
	}
	
	public int getTopInset()
	{
		java.awt.Insets insets = brass_gui.getInsets();
		int top = insets.top;
		return top;
	}
	
	public int getLeftInset()
	{
		java.awt.Insets insets = brass_gui.getInsets();
		int left = insets.left;
		return left;
	}
}
