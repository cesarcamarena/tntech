package brass;

import java.awt.Graphics;

import gui.BasicGUI;
import gui.DrawImage;
import gui.Drawable;
import gui.ImageLoader;

public class BrassGame implements Drawable
{
	private DrawImage board_img;
	private BasicGUI brass_gui;
   
   public BrassGame()
   {
		ImageLoader il = ImageLoader.getImageLoader();
		BrassXML brass_xml = new BrassXML("resources/brass_pixels.xml");
		
		gui.PixelDimension board_dimension = brass_xml.getPixelDimension("board");
		gui.PixelPoint board_center_loc = brass_xml.getPixelCenter("board");
		board_img = new DrawImage(il.getImage("images/brass_board.jpg"), "images/brass_board.jpg", board_dimension.getWidth(), board_dimension.getHeight());
		board_img.showImage(board_center_loc.getX(), board_center_loc.getY());
		
		//create the gui last
		gui.PixelDimension gui_dimension = brass_xml.getPixelDimension("gui");
		brass_gui = new BasicGUI(gui_dimension.getWidth(), gui_dimension.getHeight(), "Brass", "images/brass_icon.png", this);
   }
   
   public void draw(Graphics g, int width, int height)
   {
		board_img.draw(g);
   }
   
   public void mouseClicked(int x_click, int y_click)
	{
		System.out.println("The mouse was clicked at (" + x_click + "," + y_click + ").");
	}
   
   public void keyPressed(char key) 
	{
		System.out.println("The " + key + " key was pressed.");
	}
}
