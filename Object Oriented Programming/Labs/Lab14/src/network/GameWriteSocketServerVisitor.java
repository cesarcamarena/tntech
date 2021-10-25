package network;

import java.io.*;
import java.net.*;

public class GameWriteSocketServerVisitor implements util.GameVisitor
{
   private Socket[] sockets;
   private boolean send_client_id;
   
   public GameWriteSocketServerVisitor(Socket[] socks)
   {
	   sockets = socks;
	   send_client_id = false;
   }
   
   //the server must obtain the object input stream first
   //send the updated document to all of the clients
   public void visit(brass.BrassGame brass_game)
	{
		int num_clients = sockets.length;
		int active_client_id = brass_game.getActivePlayerID();
		if (brass_game.isComputerPlayerTurn(active_client_id)) //it is an AIs turn
		{
			brass_game.computerPlayerTurn(active_client_id);
			brass_game.repaint();
		}
		
		org.jdom2.Document doc = brass_game.writeGameXML();
		
		for (int i = 0; i < num_clients; i++)
		{
			Socket socket = sockets[i];
			try
			{
				ObjectInputStream in = new ObjectInputStream(socket.getInputStream());
				ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
				
				if (!send_client_id)
				{
					out.writeObject(i+1);
					brass_game.setTitle("Brass: Server");
				}
				else
				{
					out.writeObject(doc);
				}
				
				out.flush();
			}
			catch (IOException ioe)
			{
				System.out.println(ioe.getMessage());
				System.exit(0);
			}
		}
		
		send_client_id = true;
	}
}
