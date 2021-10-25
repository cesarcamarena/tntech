package brass;

import java.awt.Graphics;
import java.util.List;
import java.util.ArrayList;

import gui.BasicGUI;
import gui.DrawImage;
import gui.Drawable;
import gui.ImageLoader;
import gui.PixelPoint;
import gui.PixelDimension;

public class BrassGame implements Drawable
{
	private DrawImage board_img;
	private BasicGUI brass_gui;
	private BrassDeck brass_deck;
	
	//DO THIS (declare brass_players)
	private BrassPlayers brass_players;
	
   public BrassGame()
   {
		ImageLoader il = ImageLoader.getImageLoader();
		BrassXML brass_xml = new BrassXML("resources/brass_pixels.xml");
		
		PixelDimension board_dimension = brass_xml.getPixelDimension("board");
		PixelPoint board_center_loc = brass_xml.getPixelCenter("board");
		board_img = new DrawImage(il.getImage("images/brass_board.jpg"), "images/brass_board.jpg", board_dimension.getWidth(), board_dimension.getHeight());
		board_img.showImage(board_center_loc.getX(), board_center_loc.getY());
		
		brass_deck = new BrassDeck(il, brass_xml);
		brass_deck.dealStartCanalPhase();
		
		//DO THIS
		brass_players = new BrassPlayers(brass_deck, brass_xml);
		
		//create the gui last (don't move this code)
		PixelDimension gui_dimension = brass_xml.getPixelDimension("gui");
		brass_gui = new BasicGUI(gui_dimension.getWidth(), gui_dimension.getHeight(), "Brass", "images/brass_icon.png", this);
   }
   
   public void draw(Graphics g, int width, int height)
   {
		board_img.draw(g);
		brass_deck.draw(g);
		
		//DO THIS
		//draw brass_players
		brass_players.draw(g);

   }
   
   public void mouseClicked(int x_click, int y_click)
	{
		System.out.println("The mouse was clicked at (" + x_click + "," + y_click + ").");
		
		//DO THIS
		//determine if the view player needs to be changed (if so, change it)
		//call displayPlayer on BrassPlayers
		//otherwise, call nextPlayer on BrassPlayers to increment the active player
		
		int selected_player = brass_players.getSelectedPlayer(x_click, y_click); //<--- There's some code in here that deals with the area spent
		//is selected_player the same as the current viewplayer
		if (selected_player > 0)
		{
			brass_players.displayPlayer(selected_player);
			return;
		}
		
		 
		brass_players.nextPlayer();
		
	}
   
   public void keyPressed(char key) 
	{
		System.out.println("The " + key + " key was pressed.");
	}
}
