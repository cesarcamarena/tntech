package network;

import java.net.*;

public class GameServer
{
   private Socket[] clients;
   private util.GameAccept game;
   
   private GameReadSocketServerVisitor game_read;
   private GameWriteSocketServerVisitor game_write;

   public GameServer(util.GameAccept ga, int port_num, int num_clients)
   {
	   game = ga;
      clients = new Socket[num_clients];

      //watch out, this is threaded
	  //blocks for all clients to connect
      startServer(port_num, clients);
	  
	  //DO THIS
	  //set up the server socket classes
	  //perform the initial write
	  //start the server loop
	  //perform the final write
      game_read = new GameReadSocketServerVisitor(clients);
      game_write = new GameWriteSocketServerVisitor(clients);

      startServer(port_num, clients);
      
      game.accept(game_write);
	  
      serverLoop();
	  
      game.accept(game_write);
   }
   
   //the server simply collects and disseminates the game state periodically
   public void serverLoop()
   {
	   //DO THIS
	   while (!game_read.isGameOver())
      {
         try
         {
            Thread.sleep(1000);
         }

         catch (InterruptedException ie) {}

         game.accept(game_read);
         game.accept(game_write);
      }
	   
	   
	   
   }
   
   public void startServer(int port, Socket[] clients)
   {
      int num_clients = clients.length;

      try
      {
         //start the server
         ServerSocket welcomeSocket = new ServerSocket(port);
         int num_connect = 0;

         while(num_connect < num_clients)
         {
            Socket connection_socket = welcomeSocket.accept();
            clients[num_connect] = connection_socket;
            num_connect++;
         }  
      }
      catch (java.io.IOException ioe) {}

	  //blocking code
      //wait for all clients before proceeding
      //this is necessary as the above code is threaded
      boolean wait = true;
      while(wait)
      {
			wait = false;
		  
			try
			{
				Thread.sleep(1000);  //1 second
			}
			catch(InterruptedException ie) {}
		
			for (int i = 1; i <= num_clients; i++)
			{
				if (clients[i - 1] == null)
				{
					wait = true;
					break;
				}
			}
		}
   }
}
