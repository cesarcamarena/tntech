package brass;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Color;

import gui.DrawFont;
import gui.DrawImage;
import gui.HotSpot;
import gui.PixelPoint;
import gui.PixelDimension;

class BrassBoard
{
	private DrawImage board_img;
	private BrassConnections brass_connections;
	private BrassConnections brass_rails;
	private List<HotSpot> action_hot_spots;
	
	private BrassDemandTrack brass_coal_demand_track;
	private BrassDemandTrack brass_iron_demand_track;
	private BrassCottonDemandTrack brass_cotton_demand_track;
	
	public void buildLink(int link_id, int player_id)
	{
		brass_connections.buildLink(link_id, player_id);
	}
	
	public boolean isLinkConstructed(int link_id)
	{
		return brass_connections.isLinkConstructed(link_id);
	}

	public BrassBoard(BrassXML brass_xml)  
	{
		gui.ImageLoader il = gui.ImageLoader.getImageLoader();
	   
		PixelDimension board_dimension = brass_xml.getPixelDimension("board");
		PixelPoint board_center = brass_xml.getPixelCenter("board");
       
		board_img = new DrawImage(il.getImage("images/brass_board.jpg"), "Brass Board", board_dimension.getWidth(), board_dimension.getHeight());
		board_img.showImage(board_center.getX(), board_center.getY());
		
		brass_connections = new BrassCanals(brass_xml);
		brass_rails = new BrassRails(brass_xml);
		
		action_hot_spots = new ArrayList<HotSpot>();
		
		//create the action hot spots
		PixelDimension loan_dimension = brass_xml.getPixelDimension("loans");
		List<PixelPoint> loan_centers = brass_xml.getPixelCenters("loans");
		PixelPoint loan_center = loan_centers.get(0);
		HotSpot loan_ten = new HotSpot(BrassActionEnum.LOAN_10.getValue(), loan_center.getX(), loan_center.getY(), loan_dimension.getWidth(), loan_dimension.getHeight());
		action_hot_spots.add(loan_ten);
		
		loan_center = loan_centers.get(1);
		HotSpot loan_twenty = new HotSpot(BrassActionEnum.LOAN_20.getValue(), loan_center.getX(), loan_center.getY(), loan_dimension.getWidth(), loan_dimension.getHeight());
		action_hot_spots.add(loan_twenty);
		
		loan_center = loan_centers.get(2);
		HotSpot loan_thirty = new HotSpot(BrassActionEnum.LOAN_30.getValue(), loan_center.getX(), loan_center.getY(), loan_dimension.getWidth(), loan_dimension.getHeight());
		action_hot_spots.add(loan_thirty);
		
		PixelDimension link_dimension = brass_xml.getPixelDimension("link");
		PixelPoint link_center = brass_xml.getPixelCenter("link");
		HotSpot link_action = new HotSpot(BrassActionEnum.LINK.getValue(), link_center.getX(), link_center.getY(), link_dimension.getWidth(), link_dimension.getHeight());
		action_hot_spots.add(link_action);
		
		PixelDimension discard_dimension = brass_xml.getPixelDimension("discard");
		PixelPoint discard_center = brass_xml.getPixelCenter("discard");
		HotSpot discard_action = new HotSpot(BrassActionEnum.DISCARD.getValue(), discard_center.getX(), discard_center.getY(), discard_dimension.getWidth(), discard_dimension.getHeight());
		action_hot_spots.add(discard_action);
		
		PixelDimension cancel_dimension = brass_xml.getPixelDimension("cancel");
		PixelPoint cancel_center = brass_xml.getPixelCenter("cancel");
		HotSpot cancel_action = new HotSpot(BrassActionEnum.CANCEL.getValue(), cancel_center.getX(), cancel_center.getY(), cancel_dimension.getWidth(), cancel_dimension.getHeight());
		action_hot_spots.add(cancel_action);
		
		PixelDimension coal_demand_track_dim = brass_xml.getPixelDimension("coal_demand");
		List<PixelPoint> coal_demand_track_centers = brass_xml.getPixelCenters("coal_demand");
		brass_coal_demand_track = new BrassDemandTrack(il.getImage("images/coal_demand_marker.jpg"), coal_demand_track_dim, coal_demand_track_centers);
		
		PixelDimension iron_demand_track_dim = brass_xml.getPixelDimension("iron_demand");
		List<PixelPoint> iron_demand_track_centers = brass_xml.getPixelCenters("iron_demand");
		brass_iron_demand_track = new BrassDemandTrack(il.getImage("images/iron_demand_marker.jpg"), iron_demand_track_dim, iron_demand_track_centers);
		
		brass_cotton_demand_track = new BrassCottonDemandTrack(brass_xml);
   }
   
	public void draw(Graphics g)
	{
		board_img.draw(g);
		brass_connections.draw(g);
		
		brass_coal_demand_track.draw(g);
		brass_iron_demand_track.draw(g);
		brass_cotton_demand_track.draw(g);
	}
	
	public int getSelectedAction(int x, int y)
	{
		Iterator<HotSpot> action_iter = action_hot_spots.iterator();
		while(action_iter.hasNext())
		{
			HotSpot action_hot_spot = action_iter.next();
			if (action_hot_spot.isSelected(x, y))
			{
				return action_hot_spot.getHotSpotID();
			}
		}
		
		return 0;
	}
	
	public int getSelectedLink(int x, int y)
	{
		return brass_connections.getSelectedLink(x, y);
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
