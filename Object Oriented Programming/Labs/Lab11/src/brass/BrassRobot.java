package brass;

import java.awt.Robot;
import java.awt.event.InputEvent;

public class BrassRobot
{
	public static void main(String[] args)  throws java.awt.AWTException
	{
		Robot robot = null;
		
		robot = new Robot();
		robot.setAutoDelay(20);
		BrassRobot brass_robot = new BrassRobot(robot);
		brass_robot.runRobotGame();
	}
   
	private Robot robot;
	private BrassGame brass_game;
	private int x_left;
	private int y_top;
	private int left_button;

	public BrassRobot(Robot r)
	{
		robot = r;
		brass_game = new BrassGame();
		
		//a bunch of fiddling in order to get the mouse click positions relative to the board
		//and not the entire screen
		int[] screen_dimensions = brass_game.getScreenDimensions();
		int[] gui_dimensions = new int[2];
		gui_dimensions[0] = brass_game.getGUIWidth();
		gui_dimensions[1] = brass_game.getGUIHeight();
		
		int x_left_screen = screen_dimensions[0]/2 - gui_dimensions[0]/2;
		int y_top_screen = screen_dimensions[1]/2 - gui_dimensions[1]/2;
		
		int left_button_id = InputEvent.BUTTON1_MASK;
		
		//adjust the top left starting point to include the gui window and title bar
		int x_left_screen_adjustment = brass_game.getLeftInset();
		int y_top_screen_adjustment = brass_game.getTopInset();
		x_left_screen = x_left_screen + x_left_screen_adjustment;
		y_top_screen = y_top_screen + y_top_screen_adjustment;
		
		x_left = x_left_screen;
		y_top = y_top_screen;
		left_button = left_button_id;
	}
   
	public void runRobotGame()
	{	
		//yellow
		clickCard1();
		clickBuildAction();
		clickStockport();
		
		//red
		clickCard6();
		clickTechUpgradeAction();
		clickCoalToken();
		clickIronToken();
		
		//green
		clickCard2();
		clickBuildAction();
		clickCottonMillToken();
		
		//purple
		clickCard2();
		clickBuildAction();
		clickCoalToken();
		
		//red
		clickCard8();
		clickBuildAction();
		clickPortToken();
		
		clickCard2();
		clickLinkAction();
		clickLancasterPrestonCanal();
		
		//purple
		clickCard8();
		clickLinkAction();
		clickBoltonManchesterCanal();
		
		clickCard2();
		clickBuildAction();
		clickIronToken();
		
		//yellow
		clickCard4();
		clickLinkAction();
		clickMacclesfieldStockportCanal();
		
		clickCard8();
		clickLinkAction();
		clickMacclesfieldMidlandsCanal();
		
		//green
		clickCard2();
		clickLinkAction();
		clickColneYorkshireCanal();
		
		clickCard6();
		clickTechUpgradeAction();
		clickCottonMillToken();
		clickCoalToken();
		
		//green
		clickCard1();
		clickLoan30Action();
		
		clickCard2();
		clickSellCottonAction();
		
		//yellow
		clickCard1();
		clickBuildAction();
		clickCottonMillToken();
		
		clickCard7();
		clickSellCottonAction();
		
		//purple
		clickCard3();
		clickLinkAction();
		clickManchesterWarringtonCanal();
		
		clickCard2();
		clickBuildAction();
		clickWarrington();
		
		//red
		clickCard5();
		clickBuildAction();
		clickIronToken();
		
		clickCard6();
		clickTechUpgradeAction();
		clickCottonMillToken();
		clickCottonMillToken();
		
		//green
		clickCard6();
		clickLinkAction();
		clickBurnleyColneCanal();
		
		clickCard2();
		clickLinkAction();
		clickBlackburnBurnleyCanal();
		
		//red
		clickCard8();
		clickLoan30Action();
		
		clickCard4();
		clickTechUpgradeAction();
		clickCottonMillToken();
		clickPortToken();
		
		//purple
		clickCard1();
		clickLinkAction();
		clickManchesterOldhamCanal();
		
		clickCard6();
		clickLinkAction();
		clickOldhamRochdaleCanal();
		
		//yellow
		clickCard3();
		clickLoan30Action();
		
		clickCard7();
		clickBuildAction();
		clickCottonMillToken();
		
		//red
		clickCard6();
		clickBuildAction();
		clickIronToken();
		
		clickCard1();
		clickBuildAction();
		clickCoalToken();
		
		//green
		clickCard1();
		clickBuildAction();
		clickCottonMillToken();
		
		clickCard5();
		clickBuildAction();
		clickCottonMillToken();
		
		//purple
		clickCard4();
		clickTechUpgradeAction();
		clickCottonMillToken();
		clickCottonMillToken();
		
		clickCard5();
		clickLinkAction();
		clickWarringtonWiganCanal();
		
		//yellow
		clickCard1();
		clickBuildAction();
		clickCottonMillToken();
		
		clickCard7();
		clickSellCottonAction();
		
		//purple
		clickCard3();
		clickLinkAction();
		clickEllesmereWarringtonCanal();
		
		clickCard5();
		clickBuildAction();
		clickEllesmere();
		
		//yellow
		clickCard4();
		clickTechUpgradeAction();
		clickCoalToken();
		clickPortToken();
		
		clickCard1();
		clickBuildAction();
		clickIronToken();
		
		//red
		clickCard1();
		clickBuildAction();
		clickCottonMillToken();
		
		clickCard6();
		clickSellCottonAction();
		
		//green
		clickCard4();
		clickLinkAction();
		clickBlackburnWiganCanal();
		
		clickCard5();
		clickLinkAction();
		clickLiverpoolWiganCanal();
		
		//yellow
		clickCard1();
		clickTechUpgradeAction();
		clickPortToken();
		clickCottonMillToken();
		
		clickCard4();
		clickBuildAction();
		clickCoalToken();
		
		//green
		clickCard1();
		clickBuildAction();
		clickPortToken();
		
		clickCard2();
		clickSellCottonAction();
		
		//purple
		clickCard4();
		clickBuildAction();
		clickPortToken();
		
		clickCard2();
		clickLinkAction();
		clickRochdaleYorkshireCanal();
		
		//red
		clickCard3();
		clickLinkAction();
		clickBuryManchesterCanal();
		
		clickCard1();
		clickBuildAction();
		clickBury();
		
		//green
		clickCard2();
		clickBuildAction();
		clickWigan();
		
		clickCard1();
		clickSellCottonAction();
		
		//yellow
		clickCard2();
		clickTechUpgradeAction();
		clickCottonMillToken();
		clickCottonMillToken();
		
		clickCard1();
		clickBuildAction();
		clickCottonMillToken();
		
		//purple
		clickCard1();
		clickBuildAction();
		clickCoalToken();
		
		clickCard2();
		clickLoan20Action();
		
		//red
		clickCard2();
		clickLoan10Action();
		
		clickCard1();
		clickLinkAction();
		clickManchesterStockportCanal();
		
	}
	
	public void clickBlackburnBurnleyCanal()
	{
		robot.mouseMove(387 + x_left, 258 + y_top);
		robotMouseClick();
	}
	
	public void clickBlackburnWiganCanal()
	{
		robot.mouseMove(292 + x_left, 315 + y_top);
		robotMouseClick();
	}
	
	public void clickBurnleyColneCanal()
	{
		robot.mouseMove(426 + x_left, 201 + y_top);
		robotMouseClick();
	}
	
	public void clickBoltonBuryCanal()
	{
		robot.mouseMove(377 + x_left, 338 + y_top);
		robotMouseClick();
	}
	
	public void clickBoltonManchesterCanal()
	{
		robot.mouseMove(367 + x_left, 392 + y_top);
		robotMouseClick();
	}
	
	public void clickBuryManchesterCanal()
	{
		robot.mouseMove(418 + x_left, 363 + y_top);
		robotMouseClick();
	}
	
	public void clickLancasterPrestonCanal()
	{
		robot.mouseMove(247 + x_left, 172+ y_top);
		robotMouseClick();
	}
	
	public void clickFleetwoodPrestonCanal()
	{
		robot.mouseMove(212 + x_left, 223 + y_top);
		robotMouseClick();
	}
	
	public void clickPrestonWiganCanal()
	{
		robot.mouseMove(255 + x_left, 311 + y_top);
		robotMouseClick();
	}
	
	public void clickManchesterOldhamCanal()
	{
		robot.mouseMove(460 + x_left, 403 + y_top);
		robotMouseClick();
	}
	
	public void clickManchesterStockportCanal()
	{
		robot.mouseMove(432 + x_left, 473 + y_top);
		robotMouseClick();
	}
	
	public void clickManchesterWarringtonCanal()
	{
		robot.mouseMove(345 + x_left, 442 + y_top);
		robotMouseClick();
	}
	
	public void clickLiverpoolWiganCanal()
	{
		robot.mouseMove(234 + x_left, 391 + y_top);
		robotMouseClick();
	}
	
	public void clickLiverpoolEllesmereCanal()
	{
		robot.mouseMove(198 + x_left, 450 + y_top);
		robotMouseClick();
	}
	
	public void clickEllesmereWarringtonCanal()
	{
		robot.mouseMove(262 + x_left, 469 + y_top);
		robotMouseClick();
	}
	
	public void clickOldhamRochdaleCanal()
	{
		robot.mouseMove(498 + x_left, 341 + y_top);
		robotMouseClick();
	}
	
	public void clickWarringtonWiganCanal()
	{
		robot.mouseMove(279 + x_left, 391 + y_top);
		robotMouseClick();
	}
	
	public void clickMacclesfieldStockportCanal()
	{
		robot.mouseMove(440 + x_left, 538 + y_top);
		robotMouseClick();
	}
	
	public void clickColneYorkshireCanal()
	{
		robot.mouseMove(517 + x_left, 202 + y_top);
		robotMouseClick();
	}
	
	public void clickRochdaleYorkshireCanal()
	{
		robot.mouseMove(503 + x_left, 268 + y_top);
		robotMouseClick();
	}
	
	public void clickEllesmereNorthwichCanal()
	{
		robot.mouseMove(283 + x_left, 533 + y_top);
		robotMouseClick();
	}
	
	public void clickNorthwichMidlandsCanal()
	{
		robot.mouseMove(352 + x_left, 591 + y_top);
		robotMouseClick();
	}
	
	public void clickMacclesfieldMidlandsCanal()
	{
		robot.mouseMove(418 + x_left, 604 + y_top);
		robotMouseClick();
	}
	
	public void clickBarrow()
	{
		robot.mouseMove(133 + x_left, 92 + y_top);
		robotMouseClick();
	}
	
	public void clickBirkenhead()
	{
		robot.mouseMove(163 + x_left, 430 + y_top);
		robotMouseClick();
	}
	
	public void clickBlackburn()
	{
		robot.mouseMove(346 + x_left, 256 + y_top);
		robotMouseClick();
	}
	
	public void clickBolton()
	{
		robot.mouseMove(351 + x_left, 336 + y_top);
		robotMouseClick();
	}
	
	public void clickBurnley()
	{
		robot.mouseMove(422 + x_left, 228 + y_top);
		robotMouseClick();
	}
	
	public void clickBury()
	{
		robot.mouseMove(407 + x_left, 335 + y_top);
		robotMouseClick();
	}
	
	public void clickColne()
	{
		robot.mouseMove(458 + x_left, 188 + y_top);
		robotMouseClick();
	}
	
	public void clickEllesmere()
	{
		robot.mouseMove(243 + x_left, 498 + y_top);
		robotMouseClick();
	}
	
	public void clickFleetwood()
	{
		robot.mouseMove(181 + x_left, 195 + y_top);
		robotMouseClick();
	}
	
	public void clickLancaster()
	{
		robot.mouseMove(242 + x_left, 116 + y_top);
		robotMouseClick();
	}
	
	public void clickLiverpool()
	{
		robot.mouseMove(196 + x_left, 390 + y_top);
		robotMouseClick();
	}
	
	public void clickMacclesfield()
	{
		robot.mouseMove(422 + x_left, 570 + y_top);
		robotMouseClick();
	}
	
	public void clickManchester()
	{
		robot.mouseMove(416 + x_left, 447 + y_top);
		robotMouseClick();
	}
	
	public void clickOldham()
	{
		robot.mouseMove(496 + x_left, 374 + y_top);
		robotMouseClick();
	}
	
	public void clickPreston()
	{
		robot.mouseMove(258 + x_left, 228 + y_top);
		robotMouseClick();
	}
	
	public void clickRochdale()
	{
		robot.mouseMove(519 + x_left, 306 + y_top);
		robotMouseClick();
	}
	
	public void clickStockport()
	{
		robot.mouseMove(425 + x_left, 501 + y_top);
		robotMouseClick();
	}
	
	public void clickWarrington()
	{
		robot.mouseMove(294 + x_left, 445 + y_top);
		robotMouseClick();
	}
	
	public void clickWigan()
	{
		robot.mouseMove(236 + x_left, 367 + y_top);
		robotMouseClick();
	}
	
	public void clickTechUpgradeAction()
	{
		robot.mouseMove(826 + x_left, 102 + y_top);
		robotMouseClick();
	}
	
	public void clickSellCottonAction()
	{
		robot.mouseMove(626 + x_left, 102 + y_top);
		robotMouseClick();
	}
	
	public void clickLinkAction()
	{
		robot.mouseMove(629 + x_left, 169 + y_top);
		robotMouseClick();
	}
	
	public void clickBuildAction()
	{
		robot.mouseMove(729 + x_left, 129 + y_top);
		robotMouseClick();
	}
	
	public void clickLoan10Action()
	{
		robot.mouseMove(602 + x_left, 221 + y_top);
		robotMouseClick();
	}
	
	public void clickLoan20Action()
	{
		robot.mouseMove(719 + x_left, 219 + y_top);
		robotMouseClick();
	}
	
	public void clickLoan30Action()
	{
		robot.mouseMove(842 + x_left, 218 + y_top);
		robotMouseClick();
	}
	
	public void clickCoalToken()
	{
		robot.mouseMove(602 + x_left, 28 + y_top);
		robotMouseClick();
	}
	
	public void clickCottonMillToken()
	{
		robot.mouseMove(669 + x_left, 31 + y_top);
		robotMouseClick();
	}
	
	public void clickIronToken()
	{
		robot.mouseMove(731 + x_left, 29 + y_top);
		robotMouseClick();
	}
	
	public void clickPortToken()
	{
		robot.mouseMove(791 + x_left, 26 + y_top);
		robotMouseClick();
	}
	
	public void clickShipyardToken()
	{
		robot.mouseMove(846 + x_left, 30 + y_top);
		robotMouseClick();
	}
	
	public void clickCard1()
	{
		robot.mouseMove(613 + x_left, 490 + y_top);
		robotMouseClick();
	}
	
	public void clickCard2()
	{
		robot.mouseMove(686 + x_left, 486 + y_top);
		robotMouseClick();
	}
	
	public void clickCard3()
	{
		robot.mouseMove(763 + x_left, 484 + y_top);
		robotMouseClick();
	}
	
	public void clickCard4()
	{
		robot.mouseMove(836 + x_left, 485 + y_top);
		robotMouseClick();
	}
	
	public void clickCard5()
	{
		robot.mouseMove(608 + x_left, 591 + y_top);
		robotMouseClick();
	}
	
	public void clickCard6()
	{
		robot.mouseMove(683 + x_left, 591 + y_top);
		robotMouseClick();
	}
	
	public void clickCard7()
	{
		robot.mouseMove(758 + x_left, 597 + y_top);
		robotMouseClick();
	}
	
	public void clickCard8()
	{
		robot.mouseMove(837 + x_left, 597 + y_top);
		robotMouseClick();
	}
	
	public void robotMouseClick()
	{
		robot.mousePress(left_button);
		robot.mouseRelease(left_button);
	}
	
	public void robotMouseMove(int x, int y)
	{
		robot.mouseMove(x + x_left, y + y_top);
		robotMouseClick();
	}
}
