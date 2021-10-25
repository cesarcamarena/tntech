package pizza;

public class Pizza extends DecoratedPizza
{
	private Crust crust;

	public Pizza (DecoratedPizza prev_pizza, CrustSize size, CrustType type)
	{
		super(prev_pizza);

		crust = new Crust(size, type);
	}

	public double pizzaCost()
	{
		return crust.crustCost();
	}

	public String toString()
	{
		return crust.toString();
	}

	public String getImage()
	{
		return crust.getSize() + "";
	}
}