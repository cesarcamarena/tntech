package pizza;

public class PizzaFee extends DecoratedPizza
{
	String message;

	double fee;

	public PizzaFee(DecoratedPizza pizza_component, String msg, double fee)
	{
		super(pizza_component);

		message = msg;

		this.fee = fee;
	}

	public double pizzaCost()
	{
		return super.pizzaCost() + fee;
	}

	public String toString()
	{
		return super.toString() + "\n" + message;
	}
}