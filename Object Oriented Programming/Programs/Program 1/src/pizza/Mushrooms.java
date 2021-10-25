package pizza;

public class Mushrooms extends DecoratedPizza
{
	private String name;

	private double cost;

	public Mushrooms(DecoratedPizza prev_pizza)
	{
		super(prev_pizza);

		name = "M";

		cost = 0.79;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\nmushrooms";
	}

	public String getImage()
	{
		return super.getImage() + name;
	}
}