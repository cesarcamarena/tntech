package brass;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Color;

import gui.DrawFont;
import gui.DrawImage;
import gui.ImageLoader;
import gui.HotSpot;
import gui.PixelPoint;
import gui.PixelDimension;

class BrassBoard
{
	private DrawImage board_img;
	private HotSpot change_phase;
	
	private BrassConnections brass_canals;
	private BrassConnections brass_rails;
	
	private BrassDemandTrack brass_coal_demand_track;
	private BrassDemandTrack brass_iron_demand_track;
	private BrassCottonDemandTrack brass_cotton_demand_track;
	
	//private boolean rail_phase;
	
	/*
	public boolean getBrassPhase()
	{
		return rail_phase;
	}
	*/
	
	public void draw(Graphics g)
	{
		board_img.draw(g);
		
		//DO THIS draw the canals/rails depending on the phase

		/*
		if (rail_phase)
		{
			brass_rails.draw(g);
		}
		else
		{
			brass_canals.draw(g);
		}
		*/

		brass_canals.draw(g);
		
		
		
		
		brass_coal_demand_track.draw(g);
		brass_iron_demand_track.draw(g);
		brass_cotton_demand_track.draw(g);
	}
	
	//DO THIS depends on phase
	public void constructLink(int link_id, int player_id)
	{
		/*
		if (rail_phase)
		{
			brass_rails.constructLink(link_id, player_id);
		}
		else
		{
			brass_canals.constructLink(link_id, player_id);
		}
		*/
	
		brass_canals.constructLink(link_id, player_id);
	
	}
	
	//DO THIS
	public int getSelectedLink(int x, int y)
	{
		/*
		int selected_link;

		if (rail_phase)
		{
			selected_link = brass_rails.getSelectedLink(x, y);
		}
		else
		{
			selected_link = brass_canals.getSelectedLink(x, y);
		}
		*/

		return brass_canals.getSelectedLink(x, y);
	}
	
	//DO THIS
	public boolean isChangePhaseSelected(int x, int y)
	{	
		
		if (change_phase.isSelected(x, y))
		{
			brass_canals = brass_rails;

			return true;
		}

		



		return false;
	}

	public BrassBoard(BrassXML brass_xml)  
	{
		ImageLoader il = ImageLoader.getImageLoader();
	   
		PixelDimension board_dimension = brass_xml.getPixelDimension("board");
		PixelPoint board_center = brass_xml.getPixelCenter("board");
       
		board_img = new DrawImage(il.getImage("images/brass_board.jpg"), "Brass Board", board_dimension.getWidth(), board_dimension.getHeight());
		board_img.showImage(board_center.getX(), board_center.getY());
		
		//DO THIS
		brass_canals = new BrassCanals(brass_xml);
		brass_rails = new BrassRails(brass_xml);
		
		//rail_phase = false;  //game starts in the canal phase
		
		//create a hot spot to change from the canal phase to the rail phase
		PixelDimension link_dimension = brass_xml.getPixelDimension("link");
		PixelPoint link_center = brass_xml.getPixelCenter("link");
		change_phase = new HotSpot(5, link_center.getX(), link_center.getY(), link_dimension.getWidth(), link_dimension.getHeight());
		
		//add these
		PixelDimension coal_demand_track_dim = brass_xml.getPixelDimension("coal_demand");
		List<PixelPoint> coal_demand_track_centers = brass_xml.getPixelCenters("coal_demand");
		brass_coal_demand_track = new BrassDemandTrack(il.getImage("images/coal_demand_marker.jpg"), coal_demand_track_dim, coal_demand_track_centers);
		
		PixelDimension iron_demand_track_dim = brass_xml.getPixelDimension("iron_demand");
		List<PixelPoint> iron_demand_track_centers = brass_xml.getPixelCenters("iron_demand");
		brass_iron_demand_track = new BrassDemandTrack(il.getImage("images/iron_demand_marker.jpg"), iron_demand_track_dim, iron_demand_track_centers);
		
		brass_cotton_demand_track = new BrassCottonDemandTrack(brass_xml);
   }
   
   public int getCostToBuyFromCoalDemandTrack()
	{
		return brass_coal_demand_track.getCostToBuyFromDemandTrack();
	}
	
	public int getCostToBuyFromIronDemandTrack()
	{
		return brass_iron_demand_track.getCostToBuyFromDemandTrack();
	}
	
	public void buyFromCoalDemandTrack()
	{
		brass_coal_demand_track.buyFromDemandTrack();
	}
	
	public void buyFromIronDemandTrack()
	{
		brass_iron_demand_track.buyFromDemandTrack();
	}
   
}
