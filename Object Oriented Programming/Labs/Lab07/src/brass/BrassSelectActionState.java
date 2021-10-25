package brass;

class BrassSelectActionState implements BrassState
{
	private BrassGame brass_game;

	public BrassSelectActionState(BrassGame game)
	{
		brass_game = game;
	}

	public void mouseClicked(int x_click, int y_click)
	{
		//DO THIS
		//was a valid action clicked on? (getSelectedAction)
		int brass_action_id = brass_game.getSelectedAction(x_click, y_click);

		//loan action (any of the three loan amounts)
		//the loan action id is 1 for 10, 2 for 20, 3 for 30
		//refer to BrassEnum to figure out how to decode brass_action_id
		//implement the case when brass_action_id is a number representing the loan action
		if (brass_action_id >= BrassActionEnum.LOAN_10.getValue() && brass_action_id <= BrassActionEnum.LOAN_30.getValue())
		{
			int loan_amount = brass_action_id*10;
			//DO THIS
			//tell the game that a loan was selected and the amount (loanActionSelected)
			//tell the game to advance to the next player (playerActionCompleted)
			//tell the game to change the state back to select card state (changeState)

			int loan = brass_action_id * 10;

			brass_game.loanActionSelected(loan);

			brass_game.playerActionCompleted();

			BrassState select_card_state = brass_game.getSelectCardState();

			brass_game.changeState(select_card_state);
		}

		//implement the case when brass_action_id is a number representing the discard action (look in BrassEnum for the appropriate constant)
		else if (brass_action_id == BrassActionEnum.DISCARD.getValue())
		{
			//DO THIS
			//tell the game to advance to the next player
			//tell the game to change the state back to select card state

			brass_game.playerActionCompleted();

			BrassState select_card_state = brass_game.getSelectCardState();

			brass_game.changeState(select_card_state);
		}

		//cancel card selection
		else if (brass_action_id == BrassActionEnum.CANCEL.getValue())
		{
			//DO THIS
			//tell the game to cancel the card selection (do not advance to the next player)
			//tell the game to change the state back to select card state

			brass_game.cancelCardSelection();

			BrassState select_card_state = brass_game.getSelectCardState();

			brass_game.changeState(select_card_state);
		}

		//link action
		else if (brass_action_id == BrassActionEnum.LINK.getValue())
		{
			//DO THIS
			//change to BrassLinkActionState (more for the player to decide)

			BrassState link_action_state = brass_game.getLinkActionState();

			brass_game.changeState(link_action_state);
		}

	}
}
