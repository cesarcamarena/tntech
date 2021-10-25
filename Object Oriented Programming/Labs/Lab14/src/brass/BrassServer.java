package brass;

public class BrassServer
{
	public static void main(String[] args)
   {
	   int port_num = Integer.parseInt(args[0]);
	   int num_clients = Integer.parseInt(args[1]);
	   
	   network.GameServer gs = new network.GameServer(new brass.BrassGame(num_clients), port_num, num_clients);
   }
}
