package pizza;

public class GreenPeppers extends DecoratedPizza
{
	private String name;

	private double cost;

	public GreenPeppers(DecoratedPizza prev_pizza)
	{
		super(prev_pizza);

		name = "G";

		cost = 0.69;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\ngreen peppers";
	}

	public String getImage()
	{
		return super.getImage() + name;
	}
}