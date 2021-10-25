package network;

import java.io.*;
import java.net.*;

public class GameWriteSocketClientVisitor implements util.GameVisitor
{
   private Socket socket;
   private int client_id;
   private int active_client_id;
   
   public GameWriteSocketClientVisitor(int client, Socket sock)
   {
	   socket = sock;
	   client_id = client;
	   active_client_id = -1;
   }
   
   public int getClientID()
   {
	   return client_id;
   }
   
   public boolean isClientTurn()
   {
	   return (active_client_id == client_id);
   }
   
   //the client must obtain the object output stream first
   //the client must obtain both streams
   public void visit(brass.BrassGame brass_game)
	{
		//keep checking to see if the active client has finished their turn
		//if the active client is not finished, don't write anything
		active_client_id = brass_game.getActivePlayerID();
		if (isClientTurn())
		{
			return;
		}
		
		//prevent a client who is not the active client from changing the board state
		brass_game.changeState(brass_game.getGameOverState());
		brass_game.repaint();
		
		//the turn has finished, so send the document to the server
		org.jdom2.Document doc = brass_game.writeGameXML();
		try
		{
			ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
			ObjectInputStream in = new ObjectInputStream(socket.getInputStream());

			out.writeObject(doc);
			out.flush();
		}
		catch (IOException ioe)
		{
			System.out.println(ioe.getMessage());
		}
	}
}
