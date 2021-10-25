package brass;

public class BrassDriver
{
	public static void main(String[] args)
   {
	   String brass_pixels_file_name;
	   int num_players;
	   
	   if (args.length == 0)
	   {
		   brass_pixels_file_name = "resources/brass_pixels.xml";
		   num_players = 4;
	   }
	   else if (args.length == 1)
	   {
		   brass_pixels_file_name = args[0];
		   num_players = 4;
	   }
	   else
	   {
		   brass_pixels_file_name = args[0];
		   try
		   {
				num_players = Integer.parseInt(args[1]);
		   }
		   catch (NumberFormatException nfe)
		   {
				num_players = 4;
		   }
	   }
	   
		BrassGame brass_game = new BrassGame(num_players);
   }
}
