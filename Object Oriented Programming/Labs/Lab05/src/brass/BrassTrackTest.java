package brass;

import org.junit.*;
import static org.junit.Assert.*;

public class BrassTrackTest
{
	private BrassTrack bt;
	private int allowed_error;
	
	//DO THIS
	//declare a BrassCottonDemandTrack object
	private BrassCottonDemandTrack bcd;
	
	
	@Before 
	public void setUp() 
	{
		BrassXML bx = new BrassXML("resources/brass_pixels.xml");
		bt = new BrassTrack(bx);
		allowed_error = 2;  //+- two pixels is the allowed error
		
		//DO THIS (do the cotton demand track part last)
		//create a BrassCottonDemandTrack object

		bcd = new BrassCottonDemandTrack(bx);

    }
	
	
	
	@Test
	public void brassCottonDemand()
	{
		//moves the marker down and returns extra income
		int cotton_demand_extra_income = bcd.cottonTrackIncome();
		//make sure marker is in correct location
		int cotton_demand_index = bcd.getCottonDemandIndex();

		assertEquals("Cotton Demand Index 1", 2, cotton_demand_index);
		assertEquals("Cotton Demand Extra Income 1", 2, cotton_demand_extra_income);
		
		cotton_demand_extra_income = bcd.cottonTrackIncome();
		cotton_demand_index = bcd.getCottonDemandIndex();
		
		assertEquals("Cotton Demand Index 2", 3, cotton_demand_index);
		assertEquals("Cotton Demand Extra Income 2", 2, cotton_demand_extra_income);
		
		cotton_demand_extra_income = bcd.cottonTrackIncome();
		cotton_demand_index = bcd.getCottonDemandIndex();
		
		assertEquals("Cotton Demand Index 3", 6, cotton_demand_index);
		assertEquals("Cotton Demand Extra Income 3", 0, cotton_demand_extra_income);
		
		cotton_demand_extra_income = bcd.cottonTrackIncome();
		cotton_demand_index = bcd.getCottonDemandIndex();
		
		assertEquals("Cotton Demand Index 4", 8, cotton_demand_index);
		assertEquals("Cotton Demand Extra Income 4", -1, cotton_demand_extra_income);
		
		cotton_demand_extra_income = bcd.cottonTrackIncome();
		cotton_demand_index = bcd.getCottonDemandIndex();
		
		assertEquals("Cotton Demand Index 5", 8, cotton_demand_index);
		assertEquals("Cotton Demand Extra Income 5", -1, cotton_demand_extra_income);
	}
	
	//(x, y) for location 0 is specified in brass_pixels.xml
	//as it doesn't depend on the offsets, this test should certainly pass
	@Test
	public void brassLocTrackTest0()
	{
		int x_pos = bt.getXPixel(0);
		int y_pos = bt.getYPixel(0);
		
		assertTrue("Brass Track Loc X 0: TOO LOW", 322 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 0: TOO HIGH", 322 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 0: TOO LOW", 642 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 0: TOO HIGH", 642 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest1()
	{
		int x_pos = bt.getXPixel(1);
		int y_pos = bt.getYPixel(1);
		
		assertTrue("Brass Track Loc X 1: TOO LOW", 302 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 1: TOO HIGH", 302 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 1: TOO LOW", 642 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 1: TOO HIGH", 642 >= (y_pos - allowed_error));
	}
		
	@Test
	public void brassLocTrackTest5()
	{
		int x_pos = bt.getXPixel(5);
		int y_pos = bt.getYPixel(5);
		
		assertTrue("Brass Track Loc X 5: TOO LOW", 226 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 5: TOO HIGH", 226 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 5: TOO LOW", 642 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 5: TOO HIGH", 642 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest10()
	{
		int x_pos = bt.getXPixel(10);
		int y_pos = bt.getYPixel(10);

		assertTrue("Brass Track Loc X 10: TOO LOW", 132 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 10: TOO HIGH", 132 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 10: TOO LOW", 642 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 10: TOO HIGH", 642 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest16()
	{
		int x_pos = bt.getXPixel(16);
		int y_pos = bt.getYPixel(16);
		
		assertTrue("Brass Track Loc X 16: TOO LOW", 20 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 16: TOO HIGH", 20 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 16: TOO LOW", 642 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 16: TOO HIGH", 642 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest17()
	{
		int x_pos = bt.getXPixel(17);
		int y_pos = bt.getYPixel(17);
		
		assertTrue("Brass Track Loc X 17: TOO LOW", 20 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 17: TOO HIGH", 20 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 17: TOO LOW", 623 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 17: TOO HIGH", 623 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest18()
	{
		int x_pos = bt.getXPixel(18);
		int y_pos = bt.getYPixel(18);
		
		assertTrue("Brass Track Loc X 18: TOO LOW", 20 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 18: TOO HIGH", 20 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 18: TOO LOW", 605 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 18: TOO HIGH", 605 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest32()
	{
		int x_pos = bt.getXPixel(32);
		int y_pos = bt.getYPixel(32);
		
		assertTrue("Brass Track Loc X 32: TOO LOW", 245 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 32: TOO HIGH", 245 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 32: TOO LOW", 568 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 32: TOO HIGH", 568 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest46()
	{
		int x_pos = bt.getXPixel(46);
		int y_pos = bt.getYPixel(46);
		
		assertTrue("Brass Track Loc X 46: TOO LOW", 19 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 46: TOO HIGH", 19 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 46: TOO LOW", 532 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 46: TOO HIGH", 532 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest55()
	{
		int x_pos = bt.getXPixel(55);
		int y_pos = bt.getYPixel(55);
		
		assertTrue("Brass Track Loc X 55: TOO LOW", 151 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 55: TOO HIGH", 151 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 55: TOO LOW", 494 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 55: TOO HIGH", 494 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest64()
	{
		int x_pos = bt.getXPixel(64);
		int y_pos = bt.getYPixel(64);
		
		assertTrue("Brass Track Loc X 64: TOO LOW", 19 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 64: TOO HIGH", 19 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 64: TOO LOW", 458 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 64: TOO HIGH", 458 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest70()
	{
		int x_pos = bt.getXPixel(70);
		int y_pos = bt.getYPixel(70);
		
		assertTrue("Brass Track Loc X 70: TOO LOW", 94 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 70: TOO HIGH", 94 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 70: TOO LOW", 421 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 70: TOO HIGH", 421 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest76()
	{
		int x_pos = bt.getXPixel(76);
		int y_pos = bt.getYPixel(76);
		
		assertTrue("Brass Track Loc X 76: TOO LOW", 19 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 76: TOO HIGH", 19 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 76: TOO LOW", 386 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 76: TOO HIGH", 386 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest82()
	{
		int x_pos = bt.getXPixel(82);
		int y_pos = bt.getYPixel(82);
		
		assertTrue("Brass Track Loc X 82: TOO LOW", 94 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 82: TOO HIGH", 94 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 82: TOO LOW", 349 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 82: TOO HIGH", 349 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest88()
	{
		int x_pos = bt.getXPixel(88);
		int y_pos = bt.getYPixel(88);
		
		assertTrue("Brass Track Loc X 88: TOO LOW", 18 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 88: TOO HIGH", 18 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 88: TOO LOW", 311 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 88: TOO HIGH", 311 >= (y_pos - allowed_error));
	}	

	@Test
	public void brassLocTrackTest93()
	{
		int x_pos = bt.getXPixel(93);
		int y_pos = bt.getYPixel(93);
		
		assertTrue("Brass Track Loc X 93: TOO LOW", 74 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 93: TOO HIGH", 74 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 93: TOO LOW", 275 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 93: TOO HIGH", 275 >= (y_pos - allowed_error));
	}

	@Test
	public void brassLocTrackTest98()
	{
		int x_pos = bt.getXPixel(98);
		int y_pos = bt.getYPixel(98);
		
		assertTrue("Brass Track Loc X 98: TOO LOW", 18 <= (x_pos + allowed_error));
		assertTrue("Brass Track Loc X 98: TOO HIGH", 18 >= (x_pos - allowed_error));
		assertTrue("Brass Track Loc Y 98: TOO LOW", 238 <= (y_pos + allowed_error));
		assertTrue("Brass Track Loc Y 98: TOO HIGH", 238 >= (y_pos - allowed_error));
	}
	
	//(x, y) for location 1 is (302, 642)
	//(x, y) for location 5 is (226, 642)
	//(x, y) for location 10 is (132, 642)
	//(x, y) for location 16 is (20, 642)
	//(x, y) for location 17 is (20, 623)
	//(x, y) for location 18 is (20, 605)
	//(x, y) for location 32 is (245, 568)
	//(x, y) for location 46 is (19, 532)
	//(x, y) for location 55 is (151, 494)
	//(x, y) for location 64 is (19, 458)
	//(x, y) for location 70 is (94, 421)
	//(x, y) for location 76 is (19, 386)
	//(x, y) for location 82 is (94, 349)
	//(x, y) for location 88 is (18, 311)
	//(x, y) for location 93 is (74, 275)
	//(x, y) for location 98 is (18, 238)
	
	@Test
	public void brassGetIncomeAmountTest10()
	{
		int income = bt.getIncomeAmount(10);
		assertEquals("Brass Track Income 10", 0, income);
	}

	@Test
	public void brassGetIncomeAmountTest50()
	{
		int income = bt.getIncomeAmount(50);
		assertEquals("Brass Track Income 50", 17, income);
	}

	@Test
	public void brassGetIncomeAmountTest5()
	{
		int income = bt.getIncomeAmount(5);
		assertEquals("Brass Track Income 5", -5, income);
	}

	@Test
	public void brassGetIncomeAmountTest80()
	{
		int income = bt.getIncomeAmount(80);
		assertEquals("Brass Track Income 80", 25, income);
	}

	@Test
	public void brassGetIncomeAmountTest25()
	{
		int income = bt.getIncomeAmount(25);
		assertEquals("Brass Track Income 80", 8, income);
	}

	@Test
	public void brassTakeLoanTest14()
	{
		int loan_index = bt.takeLoan(14, 10);
		assertEquals("Brass Track Loan 14 for 10", 12, loan_index);
	}

}
