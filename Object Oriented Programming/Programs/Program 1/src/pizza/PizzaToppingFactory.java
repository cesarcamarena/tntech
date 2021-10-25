package pizza;

public class PizzaToppingFactory
{
	public static DecoratedPizza addPepperoni(DecoratedPizza dec_pizza)
	{
		String topping_name = "pepperoni";

		String topping_symbol = "P";

		double cost = 0.99;

		DecoratedPizza top = new PizzaTopping(dec_pizza, topping_name, topping_symbol, cost);

		return top;
	}

	public static DecoratedPizza addGreenPeppers(DecoratedPizza dec_pizza)
	{
		String topping_name = "green peppers";

		String topping_symbol = "G";

		double cost = 0.69;

		DecoratedPizza top = new PizzaTopping(dec_pizza, topping_name, topping_symbol, cost);

		return top;
	}

	public static DecoratedPizza addMushrooms(DecoratedPizza dec_pizza)
	{
		String topping_name = "mushrooms";

		String topping_symbol = "M";

		double cost = 0.79;

		DecoratedPizza top = new PizzaTopping(dec_pizza, topping_name, topping_symbol, cost);

		return top;
	}

	public static DecoratedPizza addOnions(DecoratedPizza dec_pizza)
	{
		String topping_name = "onions";

		String topping_symbol = "O";

		double cost = 0.79;

		DecoratedPizza top = new PizzaTopping(dec_pizza, topping_name, topping_symbol, cost);

		return top;
	}

	public static DecoratedPizza addSausage(DecoratedPizza dec_pizza)
	{
		String topping_name = "sausage";

		String topping_symbol = "S";

		double cost = 0.99;

		DecoratedPizza top = new PizzaTopping(dec_pizza, topping_name, topping_symbol, cost);

		return top;
	}

	public static DecoratedPizza addHam(DecoratedPizza dec_pizza)
	{
		String topping_name = "ham";

		String topping_symbol = "H";

		double cost = 0.89;

		DecoratedPizza top = new PizzaTopping(dec_pizza, topping_name, topping_symbol, cost);

		return top;
	}

	public static DecoratedPizza addPineapple(DecoratedPizza dec_pizza)
	{
		String topping_name = "pineapple";

		String topping_symbol = "A";

		double cost = 0.89;

		DecoratedPizza top = new PizzaTopping(dec_pizza, topping_name, topping_symbol, cost);

		return top;
	}
}