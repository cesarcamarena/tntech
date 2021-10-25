package brass;
import java.lang.Math;
import java.util.Comparator;

public class BrassCompareAmountSpent implements Comparator<BrassPlayer>
{
	private boolean sort;

	public BrassCompareAmountSpent(boolean sort)
	{
		this.sort = sort;
	}

	public int compare(BrassPlayer player_1, BrassPlayer player_2)
	{
		int amount_spent_1 = player_1.getAmountSpent();

		int amount_spent_2 = player_2.getAmountSpent();

		if (amount_spent_1 == amount_spent_2)
		{
			return 0;
		}

		if (amount_spent_1 < amount_spent_2)
		{
			System.out.println("Inside 2 greater");
			//return Math.abs(amount_spent_2 - amount_spent_1);
			return -1;
		}

		if (amount_spent_1 > amount_spent_2)
		{
			System.out.println("Inside 1 greater");
			return 1;
			//return Math.abs(amount_spent_1 - amount_spent_2);
		}

		return 0;
	}
}
