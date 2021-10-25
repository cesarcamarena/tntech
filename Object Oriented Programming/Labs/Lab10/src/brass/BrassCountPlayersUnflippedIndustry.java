package brass;

public class BrassCountPlayersUnflippedIndustry implements util.CountCommand<BrassIndustry>
{
	private int count;
	private int industry_id;
	private int player_id;

	public BrassCountPlayersUnflippedIndustry(int industry_id, int player_id)
	{
		count = 0;

		this.industry_id = industry_id;

		this.player_id = player_id;
	}

	public int getCount()
	{
		return count;
	}

	public void execute(BrassIndustry brass_industry)
	{
		if (brass_industry.isUnflippedIndustry(industry_id) && brass_industry.getPlayerID() == player_id)
		{
			count++;
		}
	}
}