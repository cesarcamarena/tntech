package pizza;

public class PizzaDiscount extends DecoratedPizza
{
	String message;

	double discount;

	public PizzaDiscount(DecoratedPizza pizza_component, String msg, double discount) //discount is assumed to be between 0.0 and 1.0
	{
		super(pizza_component);

		message = msg;

		this.discount = discount;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() * (1 - discount);
	}

	public String toString()
	{
		return super.toString() + "\n" + message;
	}
}