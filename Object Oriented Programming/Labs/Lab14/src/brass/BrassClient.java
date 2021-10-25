package brass;

public class BrassClient
{
	public static void main(String[] args)
	{
		String host_ip = args[0];
		int port_num = Integer.parseInt(args[1]);
		
		network.GameClient gc = new network.GameClient(new brass.BrassGame(4), host_ip, port_num);
	}
}
