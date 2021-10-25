package brass;

public class BrassCountUnflippedIndustry implements util.CountCommand<BrassIndustry>
{
	private int count;
	private int industry_id;

	public BrassCountUnflippedIndustry(int industry_id)
	{
		count = 0;
		this.industry_id = industry_id;
	}

	public int getCount()
	{
		return count;
	}

	public void execute(BrassIndustry brass_industry)
	{
		if (brass_industry.isUnflippedIndustry(industry_id))
		{
			count++;
		}
	}
}