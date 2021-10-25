package pizza;

public class Pepperoni extends DecoratedPizza
{
	private String name;

	private double cost;

	public Pepperoni(DecoratedPizza prev_pizza)
	{
		super(prev_pizza);

		name = "P";

		cost = 0.99;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\npepperoni";
	}

	public String getImage()
	{
		return super.getImage() + name;
	}
}