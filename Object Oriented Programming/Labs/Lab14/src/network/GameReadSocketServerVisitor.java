package network;

import java.io.*;
import java.net.*;

public class GameReadSocketServerVisitor implements util.GameVisitor
{
   private Socket[] sockets;
   private boolean game_over;
   
   public GameReadSocketServerVisitor(Socket[] socks)
   {
	   sockets = socks;
	   game_over = false;
   }
   
   public boolean isGameOver()
   {
	   return game_over;
   }
   
   //the server must obtain the object input stream first
   //obtain the updated document from the active client
   public void visit(brass.BrassGame brass_game)
	{
		brass_game.changeState(brass_game.getGameOverState());
		
		int num_clients = sockets.length;
		int active_client_id = brass_game.getActivePlayerID();
		//the game ended on an AI's turn
		
		if (brass_game.isGameOver())
		{
			game_over = true;
			return;
		}
		else if (brass_game.isComputerPlayerTurn(active_client_id)) //it is an AIs turn
		{
			return;  //already have the game state
		}
		
		Socket socket = sockets[active_client_id - 1];
		
		try
		{
			ObjectInputStream in = new ObjectInputStream(socket.getInputStream());
			ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());

			org.jdom2.Document doc = (org.jdom2.Document) in.readObject();
			
			brass_game.readGameXML(doc);
			brass_game.repaint();
			game_over = brass_game.isGameOver();
	System.out.println("Got game from client: " + active_client_id);
		}
		catch (IOException ioe)
		{
			System.out.println(ioe.getMessage());
			System.exit(0);
		}
		catch (ClassNotFoundException cnfe)
		{
			//this should not happen
		}
	}
}