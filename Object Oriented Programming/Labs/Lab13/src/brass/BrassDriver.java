package brass;

public class BrassDriver
{
	//DO THIS
	//process the save/load game file name parameter
	public static void main(String[] args)
   {
	   int num_players;
	   
	   if (args.length == 0)
	   {
		   num_players = 4;
	   }
	   else
	   {
		   try
		   {
				num_players = Integer.parseInt(args[0]);
		   }
		   catch (NumberFormatException nfe)
		   {
				num_players = 4;
		   }
	   }
	   
		BrassGame brass_game = new BrassGame(brass_game_file_name, num_players);
   }
}
