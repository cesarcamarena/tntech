package network;

import java.net.*;

import java.lang.Thread;

public class GameClient implements Runnable
{
	private Socket socket;  //the client connection to the network
	private util.GameAccept game;
	
	private GameReadSocketClientVisitor game_read;
	private GameWriteSocketClientVisitor game_write;

   public GameClient(util.GameAccept ga, String host_ip, int port_num)
   {
      try
      {
         socket = new Socket(host_ip, port_num);
         System.out.println("Connected!");
      }
      catch(java.io.IOException ioe)
      {
         System.out.println("Unable to connect to server.");
         System.exit(0);
      }
	  
	  game = ga;
	  
	  //DO THIS
	  //set up the client socket classes
	  //need an initial read to get the client id for GameWriteSocketClientVisitor
	  //see methods in GameReadSocketClientVisitor
	  //start up a new thread
	  game_read = new GameReadSocketClientVisitor(socket);

	  game.accept(game_read);
	  
	  game_write = new GameWriteSocketClientVisitor(game_read.getClientID(), socket);

	  Thread thread = new Thread(this);

	  thread.start();
   }
   
   public void run()
   {
	   //DO THIS
	   //while the game is not over, see whose turn it is (isClientTurn)
	   //while this client is taking their turn (another loop, not waiting for the server)
       //then check periodically (every 2 seconds) to see if they have finished
	   //when done, the current player will send the game state to the server
	   
	   //at the bottom of the outer loop, all clients block until the server updates the game state
	   //the client whose turn it is now enters the inner loop and takes their turn

   		while (!game_read.isGameOver())
   		{
	   		if(game_read.isClientTurn())
	   		{
	   			game.accept(game_write);
	   			while (game_write.isClientTurn())
	   			{
	   				try
	   				{
	   					Thread.sleep(2000);
	   				}

	   				catch (InterruptedException ie) {}

	   				game.accept(game_write);
	   			}
	   		}
			try
			{
				Thread.sleep(2000);
			}
			catch (InterruptedException ie) {}

			game.accept(game_read);
   		}	
	
	  
   }
}
