package brass;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

import gui.PixelPoint;
import gui.PixelDimension;

class BrassXML
{
	private org.jdom2.Element root_element;
	
	public BrassXML(String file_name)
	{
		java.io.File file = new java.io.File(file_name);
      
		org.jdom2.input.SAXBuilder saxb = new org.jdom2.input.SAXBuilder();
        org.jdom2.Document doc = null;
		
		try
		{
			doc = saxb.build(file);
		}
		catch(org.jdom2.JDOMException jdome) 
		{
			System.out.println(jdome.getMessage());
		}
		catch(Exception jdome) 
		{
			System.out.println(jdome.getMessage());
		}
		
		root_element = doc.getRootElement();
	}
	
	public PixelDimension getPixelDimension(String image_element_name)
	{
		if (root_element == null) return null;
		
		org.jdom2.Element brass_image_element = root_element.getChild(image_element_name);
		org.jdom2.Element dimensions_element = brass_image_element.getChild("dimensions");
		org.jdom2.Element width_element = dimensions_element.getChild("width");
		org.jdom2.Element height_element = dimensions_element.getChild("height");
	  
		int w = Integer.parseInt(width_element.getText());
		int h = Integer.parseInt(height_element.getText());

		return new PixelDimension(w, h);
	}
	
	public PixelPoint getPixelCenter(String image_element_name)
	{
		if (root_element == null) return null;
		
		org.jdom2.Element brass_image_element = root_element.getChild(image_element_name);
		org.jdom2.Element pixel_center_element = brass_image_element.getChild("center");
		org.jdom2.Element x_center_element = pixel_center_element.getChild("x");
		org.jdom2.Element y_center_element = pixel_center_element.getChild("y");
		
		int x = Integer.parseInt(x_center_element.getText());
		int y = Integer.parseInt(y_center_element.getText());
		return new PixelPoint(x, y);
	}
	
	public List<PixelPoint> getPixelCenters(String image_element_name)
	{
		if (root_element == null) return null;
		
		org.jdom2.Element brass_image_element = root_element.getChild(image_element_name);
		
		List<PixelPoint> pixel_centers = new ArrayList<PixelPoint>();
		
		List<org.jdom2.Element> pixel_centers_element = brass_image_element.getChildren("center");
		Iterator<org.jdom2.Element> pixel_centers_element_iter = pixel_centers_element.iterator();
		while(pixel_centers_element_iter.hasNext())
		{
			org.jdom2.Element pixel_center_element = pixel_centers_element_iter.next();
			org.jdom2.Element x_center_element = pixel_center_element.getChild("x");
			org.jdom2.Element y_center_element = pixel_center_element.getChild("y");
			int x = Integer.parseInt(x_center_element.getText());
			int y = Integer.parseInt(y_center_element.getText());
			
			PixelPoint pixel_point = new PixelPoint(x, y);
			pixel_centers.add(pixel_point);
		}
		
		return pixel_centers;
	}
	
	public int getTextSize(String image_element_name)
	{
		if (root_element == null) return 0;
		
		org.jdom2.Element brass_text_element = root_element.getChild(image_element_name);
		org.jdom2.Element text_size_element = brass_text_element.getChild("size");
		int size = Integer.parseInt(text_size_element.getText());
		return size;
	}
}
