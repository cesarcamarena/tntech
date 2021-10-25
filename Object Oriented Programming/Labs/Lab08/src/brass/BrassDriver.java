package brass;

public class BrassDriver
{

	public static void main(String[] args)
   {
	   int num_players;

		//DO THIS
		//obtain the number of players from the args array
		//use try-catch as necessary (NumberFormatException)
		//the default value for number of players is 4 in case of a problem (NumberFormatException)
		//or if no arguments have been passed to main

	   	try
		   {
   			num_players = Integer.parseInt(args[0]);

   			if (num_players < 0 || num_players > 4)
   			{
   				throw new ArrayIndexOutOfBoundsException();
   			}
   		}

   		catch (ArrayIndexOutOfBoundsException aioobe)
   		{
   			num_players = 4;
   		}

   		catch (NumberFormatException nfe)
   		{
   			num_players = 4;
   		}

   		

		BrassGame brass_game = new BrassGame(num_players);
   }
}
