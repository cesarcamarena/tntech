package brass;

//DO THIS
//a CANAL costs 3, a RAIL costs 5, and a SECOND_RAIL costs 10
enum BrassLinkCostEnum
{
	CANAL(3), RAIL(5), SECOND_RAIL(10);
	
	private int value;
	
	private BrassLinkCostEnum(int val) 
	{ 
		value = val; 
	}
	
	public int getValue() 
	{ 
		return value; 
	}
};