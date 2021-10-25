package brass;

public class BrassCountConstructedPorts implements util.CountCommand<BrassIndustry>
{
	private int count;

	public BrassCountConstructedPorts()
	{
		count = 0;
	}

	public int getCount()
	{
		return count;
	}

	public void execute(BrassIndustry brass_industry)
	{
		if (brass_industry.isConstructedPort())
		{
			count++;
		}
	}
}