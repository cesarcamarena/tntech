package pizza;

public class Onions extends DecoratedPizza
{
	private String name;

	private double cost;

	public Onions(DecoratedPizza prev_pizza)
	{
		super(prev_pizza);

		name = "O";

		cost = 0.79;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\nonions";
	}

	public String getImage()
	{
		return super.getImage() + name;
	}
}