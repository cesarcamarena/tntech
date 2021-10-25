package brass;

public class BrassDriver
{
	public static void main(String[] args)
   {
	   String brass_game_file_name;
	   int num_players;
	   
	   if (args.length == 0)
	   {
		   brass_game_file_name = "resources/brass_game.xml";
		   num_players = 4;
	   }
	   else if (args.length == 1)
	   {
		   brass_game_file_name = args[0];
		   num_players = 4;
	   }
	   else
	   {
		   brass_game_file_name = args[0];
		   try
		   {
				num_players = Integer.parseInt(args[1]);
		   }
		   catch (NumberFormatException nfe)
		   {
				num_players = 4;
		   }
	   }
	   
		BrassGame brass_game = new BrassGame(brass_game_file_name, num_players);
   }
}
