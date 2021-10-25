package pizza;

import util.Keyboard;
import java.text.DecimalFormat;

public class PizzaDriver
{
	private static int menu() //show the menu choices, wait for and return the valid selection
	{
		System.out.println("\n1. Meat Lover's");
		System.out.println("2. Veggie Lover's");
		System.out.println("3. Hawaiin");
		System.out.println("4. Build Your Own");

		Keyboard kb = Keyboard.getKeyboard();

		int selection = kb.readInt("\nSelect from the above: ");

		System.out.println(selection);

		while (selection < 1 || selection > 4)
		{
			System.out.println("\n\nPlease select a number from 1-4.");
			System.out.println("\n1. Meat Lover's");
			System.out.println("\n2. Veggie Lover's");
			System.out.println("\n3. Hawaiin");
			System.out.println("\n4. Build Your Own\n\n");

			System.out.println(selection);

			selection = kb.readInt("Select from the above: ");
		}

		return selection;
	}

	private static void requestSize(PizzaBuilder pizza_builder) //request the crust size, wait for a valid response confirmation from PizzaBuilder
	{
		Keyboard kb = Keyboard.getKeyboard();

		String response = kb.readString("What size pizza (S/M/L)? ");

		System.out.println(response);

		char response_char = response.charAt(0);

		boolean was_added = pizza_builder.setSize(response_char);

		while (was_added == false)
		{
			response = kb.readString("What size pizza (S/M/L)? ");

			System.out.println(response);

			response_char = response.charAt(0);

			was_added = pizza_builder.setSize(response_char);
		}
	}

	private static void requestCrust(PizzaBuilder pizza_builder) //request the crust type, wait for a valid response confirmation from PizzaBuilder
	{
		Keyboard kb = Keyboard.getKeyboard();

		String response = kb.readString("What type of crust (thin/hand/pan)? ");

		System.out.println(response);

		boolean was_added = pizza_builder.setCrust(response);

		while (was_added == false)
		{
			System.out.println("\n\nPlease put in a valid input.\n\n");

			response = kb.readString("What type of crust (thin/hand/pan)? ");

			System.out.println(response);

			was_added = pizza_builder.setCrust(response);
		}
	}

	private static void requestToppings(PizzaBuilder pizza_builder) //ask for toppings until Done indicated (invalid toppings are ignored)
	{
		Keyboard kb = Keyboard.getKeyboard();

		String response = kb.readString("(P)epperoni, (O)nions, (G)reen Peppers, (S)ausage, (M)ushrooms, (D)one\n");

		System.out.println(response);

		char response_char = response.charAt(0);

		pizza_builder.addTopping(response_char);

		while (!response.equals("d") && !response.equals("D") && !response.equals("done") && !response.equals("Done"))
		{
			response = kb.readString("(P)epperoni, (O)nions, (G)reen Peppers, (S)ausage, (M)ushrooms, (D)one\n");

			System.out.println(response);

			response_char = response.charAt(0);

			pizza_builder.addTopping(response_char);
		}
	}

	private static void showOrder(DecoratedPizza dec_pizza) //display the pizza and its total cost
	{
		DecimalFormat decimal_format = new DecimalFormat("$###.##");

		System.out.println("\nYour pizza:");

		String pizza = dec_pizza.toString();

		System.out.println(pizza);

		double pizza_cost = dec_pizza.pizzaCost();
		String string_cost = decimal_format.format(pizza_cost);

		System.out.println("\nThe cost of your pizza is " + string_cost);
	}

	public static void main (String[] args) //allow the user to order multiple pizzas if desired, call the other methods, track total cost and number of pizzas
	{
		PizzaBuilder pizza_builder = new PizzaBuilder();

		String SENTINEL = "n";

		DecimalFormat decimal_format = new DecimalFormat("$###.##");

		double total_cost = 0.00;

		int number_of_pizzas = 0;

		DecoratedPizza pizza;

		Keyboard kb = Keyboard.getKeyboard();

		String response = kb.readString("Would you like to order a pizza (y/n)? ");

		System.out.println(response);

		response = response.toLowerCase();

		while (!response.equals("y") && !response.equals("yes") && !response.equals("n") && !response.equals("no"))
		{
			System.out.println("\nPlease choose y or n.\n");

			response = kb.readString("Would you like to order a pizza (y/n)? ");

			System.out.println(response);

			response = response.toLowerCase();
		}

		while (!response.equals(SENTINEL) && !response.equals("no"))
		{
			if (response.equals("y") || response.equals("yes"))
			{
				int choice = menu();

				if (choice == 1)
				{
					pizza_builder = new MeatLovers();

					requestSize(pizza_builder);

					requestCrust(pizza_builder);
				}

				if (choice == 2)
				{
					pizza_builder = new VeggieLovers();

					requestSize(pizza_builder);

					requestCrust(pizza_builder);
				}

				if (choice == 3)
				{
					pizza_builder = new Hawaiian();

					requestSize(pizza_builder);

					requestCrust(pizza_builder);
				}

				if (choice == 4)
				{
					pizza_builder = new PizzaBuilder();

					requestSize(pizza_builder);

					requestCrust(pizza_builder);

					requestToppings(pizza_builder);
				}

				response = kb.readString("Are you senior citizen (y/n)? ");

				System.out.println(response);

				if (response.equals("y") || response.equals("yes"))
				{
					pizza_builder.addDiscount();
				}

				response = kb.readString("Do you need this pizza delivered (y/n)? ");

				System.out.println(response);

				if (response.equals("y") || response.equals("yes"))
				{
					pizza_builder.addFee();
				}

				pizza = pizza_builder.pizzaDone();
				
				showOrder(pizza);

				total_cost += pizza.pizzaCost();

				number_of_pizzas++;

				response = kb.readString("\nWould you like to order another pizza (y/n)? ");

				System.out.println(response);

				response = response.toLowerCase();
			}
		}

		String string_total_cost = decimal_format.format(total_cost);
		System.out.println("You ordered " + number_of_pizzas + " pizza(s) for a grand total of " + string_total_cost);
	}
}