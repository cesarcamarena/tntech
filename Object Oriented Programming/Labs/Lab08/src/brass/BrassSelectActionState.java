package brass;

class BrassSelectActionState implements BrassState
{
	private BrassGame brass_game;
	private int brass_card_city_tech_id; //brass_card_id is the city/industry identifier for the card

	//DO THIS
	//need a setSelectedCard method to store the forwarded information (integer parameter) in brass_card_city_tech_id
	public void setSelectedCard(int id)
	{
		System.out.println("CARD SELECTED" +id);
		brass_card_city_tech_id = id;
	}

	public BrassSelectActionState(BrassGame game)
	{
		brass_game = game;
		brass_card_city_tech_id = 0;
	}

	public void mouseClicked(int x_click, int y_click)
	{
		//was a valid action clicked on?
		int brass_action_id = brass_game.getSelectedAction(x_click, y_click);

		//loan action (simple enough to be handled right here)
		//the loan action id is 1 for 10, 2 for 20, 3 for 30

		//this action can actually fail if the user's income index will fall below -10
		//should check for this before reaching this point
		if ((brass_action_id >= BrassActionEnum.LOAN_10.getValue()) && (brass_action_id <= BrassActionEnum.LOAN_30.getValue()))
		{
			int loan_amount = brass_action_id*10;
			brass_game.loanActionSelected(loan_amount);

			//the action was successful, advance to next player
			brass_game.playerActionCompleted();

			//change the current state in brass game
			brass_game.changeState(brass_game.getSelectCardState());
		}

		//DO THIS
		//use BrassActionEnum.BUILD
		//forward required information to BrassBuildActionState
		else if (brass_action_id == BrassActionEnum.BUILD.getValue())
		{
			//change the current state in brass game (forward the city/industry card information):
			//first, call getBuildActionState on brass_game
			//second, setCardSelected() on build_action_state
			//third, changeState() on brass_game

			BrassState build_action_state = brass_game.getBuildActionState();

			brass_game.changeState(build_action_state);

			((BrassBuildActionState)build_action_state).setSelectedCard(brass_card_city_tech_id);//or here
		}

		else if (brass_action_id == BrassActionEnum.LINK.getValue())
		{
			brass_game.changeState(brass_game.getLinkActionState());
		}

		//discard
		else if (brass_action_id == BrassActionEnum.DISCARD.getValue())
		{
			brass_game.playerActionCompleted();
			brass_game.changeState(brass_game.getSelectCardState());
		}

		//cancel card selection
		else if (brass_action_id == BrassActionEnum.CANCEL.getValue())
		{
			brass_game.cancelCardSelection();
			brass_game.changeState(brass_game.getSelectCardState());
		}
	}
}
