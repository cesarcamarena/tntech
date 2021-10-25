package pizza;

public class PizzaBuilder
{
	private DecoratedPizza top;
	private CrustSize size;
	private CrustType type;
	private PizzaToppingFactory topping_factory;

	protected void buildPizza() //create a Crust and a Pizza using that Crust based on the user's specifications (the Pizza is now ready for toppings)
	{
		this.top = new Pizza(top, size, type);
	}

	public PizzaBuilder() //start with a small, thin pizza with no toppings as the default
	{
		CrustSize small_size = CrustSize.S;

		CrustType thin_type = CrustType.THIN;

		this.top = new Pizza(top, small_size, thin_type);
	}

	public boolean setSize(char try_size) //returns true if the input was valid ("S" or "small", etc., not case sensitive)
	{
		String string_try_size = Character.toString(try_size);

		string_try_size = string_try_size.toLowerCase();

		if (string_try_size.equals("s"))
		{
			this.size = CrustSize.S;

			buildPizza();

			return true;
		}

		if (string_try_size.equals("m"))
		{
			this.size = CrustSize.M;

			buildPizza();

			return true;
		}

		if (string_try_size.equals("l"))
		{
			this.size = CrustSize.L;

			buildPizza();

			return true;
		}

		return false;
	}

	public boolean setCrust(String try_crust) //("thin", "hand", or "pan", not case sensitive)
	{
		try_crust = try_crust.toLowerCase();

		if (try_crust.equals("t") || try_crust.equals("thin"))
		{
			this.type = CrustType.THIN;

			buildPizza();

			return true;
		}

		if (try_crust.equals("h") || try_crust.equals("hand"))
		{
			this.type = CrustType.HAND;

			buildPizza();

			return true;
		}

		if (try_crust.equals("p") || try_crust.equals("pan"))
		{
			this.type = CrustType.PAN;

			buildPizza();

			return true;
		}

		return false;
	}

	public void addTopping(char topping_char) //compare the topping abbreviation to topping_char to determine which topping to add (using void here is convenient for the PizzaDriver, ignore invalid abbreviations)
	{
		String string_topping_char = Character.toString(topping_char);

		string_topping_char = string_topping_char.toLowerCase();
		
		if (top instanceof PizzaDiscount)
		{
			return;
		}

		if (string_topping_char.equals("p"))
		{
			DecoratedPizza p = topping_factory.addPepperoni(top);

			this.top = p;
		}

		if (string_topping_char.equals("o"))
		{
			DecoratedPizza o = topping_factory.addOnions(top);

			this.top = o;
		}

		if (string_topping_char.equals("m"))
		{
			DecoratedPizza m = topping_factory.addMushrooms(top);

			this.top = m;
		}

		if (string_topping_char.equals("g"))
		{
			DecoratedPizza g = topping_factory.addGreenPeppers(top);

			this.top = g;
		}

		if (string_topping_char.equals("s"))
		{
			DecoratedPizza s = topping_factory.addSausage(top);

			this.top = s;
		}

		if (string_topping_char.equals("h"))
		{
			DecoratedPizza h = topping_factory.addHam(top);

			this.top = h;
		}

		if (string_topping_char.equals("a"))
		{
			DecoratedPizza a = topping_factory.addPineapple(top);

			this.top = a;
		}

		return;
	}

	public void addDiscount()
	{
		if (top instanceof PizzaDiscount || top instanceof PizzaTopping || top instanceof Pizza)
		{
			DecoratedPizza discount = new PizzaDiscount(top, "senior discount", 0.1);

			this.top = discount;
		}
	}

	public void addFee()
	{
		DecoratedPizza fee = new PizzaFee(top, "delivery", 2.50);

		this.top = fee;
	}

	public DecoratedPizza pizzaDone() //return the final DecoratedPizza and reset to the default pizza if another pizza is desired
	{
		return this.top;
	}
}