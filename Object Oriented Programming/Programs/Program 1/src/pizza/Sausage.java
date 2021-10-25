package pizza;

public class Sausage extends DecoratedPizza
{
	private String name;

	private double cost;

	public Sausage(DecoratedPizza prev_pizza)
	{
		super(prev_pizza);

		name = "S";

		cost = 0.99;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\nsausage";
	}

	public String getImage()
	{
		return super.getImage() + name;
	}
}