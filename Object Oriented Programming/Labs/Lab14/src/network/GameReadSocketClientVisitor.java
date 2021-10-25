package network;

import java.io.*;
import java.net.*;

public class GameReadSocketClientVisitor implements util.GameVisitor
{
   private Socket socket;
   private boolean game_over;
   private int active_client_id;
   private int client_id;
   
   public GameReadSocketClientVisitor(Socket sock)
   {
	   socket = sock;
	   active_client_id = -1;
	   client_id = -1;
	   game_over = false;
   }
   
   public boolean isGameOver()
   {
	   return game_over;
   }
   
   public boolean isClientTurn()
   {
	   return (active_client_id == client_id);
   }
   
   public int getClientID()
   {
	   return client_id;
   }
   
   public void visit(brass.BrassGame brass_game)
	{
		brass_game.changeState(brass_game.getGameOverState());
		
		try
		{
			ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
			ObjectInputStream in = new ObjectInputStream(socket.getInputStream());
			
			if (client_id == -1)
			{
				client_id = (Integer) in.readObject();
				if (client_id == 1)
				{
					brass_game.setTitle("Brass: Red");
					System.out.println("You are red.");
				}
				else if (client_id == 2)
				{
					brass_game.setTitle("Brass: Purple");
					System.out.println("You are purple.");
				}
				else if (client_id == 3)
				{
					brass_game.setTitle("Brass: Green");
					System.out.println("You are green.");
				}
				else
				{
					brass_game.setTitle("Brass: Yellow");
					System.out.println("You are yellow.");
				}
				return;
			}

			org.jdom2.Document doc = (org.jdom2.Document) in.readObject();
			
			brass_game.readGameXML(doc);
			
			brass_game.repaint();
			active_client_id = brass_game.getActivePlayerID();
			game_over = brass_game.isGameOver();
	System.out.println("Got game from server.");
			
			if (isClientTurn())
			{
				brass_game.changeState(brass_game.getSelectCardState());
	System.out.println("It's your turn.");
			}
			
			if (isGameOver())
			{
				brass_game.changeState(brass_game.getGameOverState());
			}
		
		}
		catch (IOException ioe)
		{
			System.out.println(ioe.getMessage());
		}
		catch (ClassNotFoundException cnfe)
		{
			//this should not happen
		}
	}
}
