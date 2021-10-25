package brass;

enum BrassIndustryEnum 
{
	COAL (1,"coal"), COTTON (2,"cotton"), IRON (3,"iron"), PORT (4,"port"), SHIP (5,"ship");
	private int value;
	private String name;
	
	private BrassIndustryEnum(int val, String n) 
	{ 
		value = val;
		name = n;
	}
	
	public int getValue() 
	{ 
		return value; 
	}
	
	public String getName() 
	{ 
		return name; 
	}
};

enum BrassConnectionSearchEnum 
{
	DEPTH_LIMIT (1), BREADTH_FIRST (2);
	private int value;
	
	private BrassConnectionSearchEnum(int val) 
	{ 
		value = val; 
	}
	
	public int getValue() 
	{ 
		return value; 
	}
};

enum BrassActionEnum 
{
	LOAN_10 (1), LOAN_20 (2), LOAN_30 (3), BUILD (4), LINK (5), SELL (6), UPGRADE (7), DISCARD (8), CANCEL (9), DOUBLE_CARD(10), DOUBLE_RAIL(11), REPLACE(12);
	private int value;
	
	private BrassActionEnum(int val) 
	{ 
		value = val; 
	}
	
	public int getValue() 
	{ 
		return value; 
	}
};

enum BrassLinkCostEnum
{
	CANAL (3), RAIL (5), DOUBLE_RAIL(10);
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
