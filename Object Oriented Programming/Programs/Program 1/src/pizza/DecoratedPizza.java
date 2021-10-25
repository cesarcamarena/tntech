package pizza;

public abstract class DecoratedPizza
{
	private DecoratedPizza next_pizza_item;

	public DecoratedPizza()
	{
		next_pizza_item = null;
	}

	public DecoratedPizza(DecoratedPizza np)
	{
		next_pizza_item = np;
	}

	public double pizzaCost() //get the cost from the "next_pizza_item" DecoratedPizza
	{
		if (next_pizza_item == null)
		{
			return 0.0;
		}

		return next_pizza_item.pizzaCost();
	}

	public String toString() //get the state of the "next_pizza_item" DecoratedPizza
	{
		if (next_pizza_item == null)
		{
			return "";
		}

		return next_pizza_item.toString();
	}

	public String getImage() //get the abbreviation of the "next_pizza_item" 
	{
		if (next_pizza_item == null)
		{
			return "";
		}

		return next_pizza_item.getImage();
	}

}