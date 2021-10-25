package gui;

import java.awt.*;
import java.awt.image.*;
import javax.imageio.*;
import java.io.*;

public class ImageLoader
{
   private static ImageLoader il = new ImageLoader();
   private Toolkit toolkit;

   //singleton design pattern hides the constructor
   private ImageLoader() 
   {
      toolkit = Toolkit.getDefaultToolkit();
   }

   //the only way to get at the singleton reference
   public static ImageLoader getImageLoader()
   {
      return il;
   }
   
   public Image getImage(String file_name)
   {
      int len = file_name.length();
      Image img = null;   

      try
      {
		  BufferedImage bi = ImageIO.read(new File(file_name));
         //BufferedImage bi = ImageIO.read(getClass().getResource(file_name));
         img = toolkit.createImage(bi.getSource());
      } 
      catch (IOException e){}
      
      return img;
   }
   
   public Image getFilteredImage(Image img, ImageFilter img_filter)
   {
		FilteredImageSource fis = new FilteredImageSource(img.getSource(), img_filter);
		return toolkit.createImage(fis);
   }
   
   public Image getTransparentImage(Image img, Color color)
   {
	    ImageFilter img_filter = new TransparencyFilter(color);
		FilteredImageSource fis = new FilteredImageSource(img.getSource(), img_filter);
		return toolkit.createImage(fis);
   }
}

class TransparencyFilter extends RGBImageFilter
{
    // the color we are looking for... alpha bits are set to opaque
    private int marker_rgb;
 
    //the transparent color is specified through the constructor
    public TransparencyFilter(Color color)  
    {
       marker_rgb = (color.getRGB() | 0xFF000000);
    }

	//on a pixel by pixel basis, determine if alpha should be set to zero
    public int filterRGB(int x, int y, int rgb) 
    {
        if ((rgb | 0xFF000000) == marker_rgb) 
        {
           // Mark the alpha bits as zero - transparent
           return 0x00FFFFFF & rgb;
        }
		
		return rgb;
    }
}
