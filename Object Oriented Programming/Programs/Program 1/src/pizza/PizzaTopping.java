package pizza;

public class PizzaTopping extends DecoratedPizza
{
	private DecoratedPizza decorated_pizza;

	private String name;

	private String symbol;

	private double cost;

	public PizzaTopping(DecoratedPizza pizza_component, String topping_string, String topping_letter, double topping_cost)
	{
		super(pizza_component);

		name = topping_string;

		symbol = topping_letter;

		cost = topping_cost;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + cost;
	}

	public String toString()
	{
		return super.toString() + "\n" + name;
	}

	public String getImage()
	{
		return super.getImage() + symbol;
	}
}

//9319821053