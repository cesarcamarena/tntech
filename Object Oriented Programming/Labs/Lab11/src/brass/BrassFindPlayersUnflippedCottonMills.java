package brass;

import java.util.List;
import java.util.ArrayList;
import util.CountCommand;

public class BrassFindPlayersUnflippedCottonMills implements util.FindCommand<BrassCity>
{
	private int player_id;

	private List<Integer> unflipped_cotton_mills;

	public BrassFindPlayersUnflippedCottonMills(int player_id)
	{
		this.player_id = player_id;

		unflipped_cotton_mills = new ArrayList<Integer>();
	}

	public List<Integer> getList()
	{
		return unflipped_cotton_mills;
	}

	public void execute(BrassCity brass_city)
	{
		CountCommand<BrassIndustry> count_cotton_mills = new BrassCountPlayersUnflippedIndustry(2, player_id); //2 is the enum for Cotton Mill

		brass_city.execute(count_cotton_mills);

		int count = count_cotton_mills.getCount();

		while (count > 0)
		{
			unflipped_cotton_mills.add(brass_city.getCityID());
			count--;
		}
	}
}