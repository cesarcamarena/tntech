package pizza;

public class Pineapple extends DecoratedPizza
{
	private String name;

	private double cost;

	public Pineapple(DecoratedPizza prev_pizza)
	{
		super(prev_pizza);

		name = "A";

		cost = 0.89;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\npineapple";
	}

	public String getImage()
	{
		return super.getImage() + name;
	}
}