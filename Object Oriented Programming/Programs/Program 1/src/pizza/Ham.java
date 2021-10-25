package pizza;

public class Ham extends DecoratedPizza
{
	private String name;

	private double cost;

	public Ham(DecoratedPizza prev_pizza)
	{
		super(prev_pizza);

		name = "H";

		cost = 0.89;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\nham";
	}

	public String getImage()
	{
		return super.getImage() + name;
	}
}