package pizza;

public class VeggieLovers extends PizzaBuilder
{
	public VeggieLovers()
	{
		super();
	}

	public void buildPizza()
	{
		super.buildPizza();

		super.addTopping('G');

		super.addTopping('M');

		super.addTopping('O');
	}
}