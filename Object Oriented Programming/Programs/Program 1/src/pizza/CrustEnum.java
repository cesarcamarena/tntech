package pizza;

enum CrustSize
{
	S(5.99), M(7.99), L(9.99);

	private double cost;

	private CrustSize(double c)
	{
		cost = c;
	}

	public double getCost()
	{
		return cost;
	}
}

enum CrustType
{
	THIN(0.00), HAND(0.50), PAN(1.00);

	private double cost;

	private CrustType(double c)
	{
		cost = c;
	}

	public double getCost()
	{
		return cost;
	}
}