package brass;

import gui.DrawImage;
import gui.PixelPoint;

import java.awt.Image;
import java.awt.Graphics;
import java.util.List;

class BrassToken
{
	private DrawImage big_image;  //not yet built
	private DrawImage small_image;  //after built

	private int token_id;
	private int player_id;  	//owning player
	private int industry_id;
	
	private int cost;
	private int victory;
	private int cubes;
	private boolean coal_requirement;
	private boolean iron_requirement;
	private int income;
	private int tech_level;
	
	private boolean flipped;
	private int period;
	
	//put the token on the player's display in the correct location based on industry
	public void placePlayerToken(int x, int y)
	{
		big_image.showImage(x, y);
	}

	public void drawPlayerToken(Graphics g)
	{
		big_image.draw(g);
	}
	
	public BrassToken(int t_id, int industry, int tech, int cost, int income, int victory, int cubes, boolean coal, boolean iron, int period, int player, Image big, int w_b, int h_b, Image small, int w_s, int h_s)
	{	
		token_id = t_id;
		big_image = new DrawImage(big, "Big Token", w_b, h_b);
		small_image = new DrawImage(small, "Small Token", w_s, h_s);
		
		industry_id = industry;
		tech_level = tech;
		this.cost = cost;
		this.income = income;
		this.victory = victory;
		coal_requirement = coal;
		iron_requirement = iron;
		this.period = period;
		this.cubes = cubes;
		
		player_id = player;
		flipped = false;
	}
}
