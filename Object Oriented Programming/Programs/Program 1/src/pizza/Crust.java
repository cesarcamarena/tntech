package pizza;

public class Crust
{
	private CrustSize size;
	private CrustType type;

	public Crust(CrustSize s, CrustType t)
	{
		size = s;
		type = t;
	}

	public String getCrust()
	{
		if (type == CrustType.THIN)
		{
			return "THIN";
		}

		if (type == CrustType.HAND)
		{
			return "HAND";
		}

		if (type == CrustType.PAN)
		{
			return "PAN";
		}

		return "";
	}

	public char getSize()
	{
		if (size == CrustSize.S)
		{
			return 'S';
		}

		if (size == CrustSize.M)
		{
			return 'M';
		}

		if (size == CrustSize.L)
		{
			return 'L';
		}

		return ' ';
	}

	public double crustCost()
	{
		return size.getCost() + type.getCost();
	}

	public String toString()
	{
		return "Size: " + getSize() + "\nCrust: " + getCrust();
	}

}