package brass;

class BrassSelectCardState implements BrassState
{
	private BrassGame brass_game;

	public BrassSelectCardState(BrassGame game)
	{
		brass_game = game;
	}

	// BrassGame tells the State class where the mouse was clicked
	public void mouseClicked(int x_click, int y_click)
	{
		//first check to see if view player was changed
		int active_player_id = brass_game.getActivePlayerID();
		int display_player_id = brass_game.getSelectedPlayer(x_click, y_click);
		if (display_player_id > 0)
		{
			brass_game.displayPlayer(display_player_id); //perhaps player wants to view a different player
			return;
		}

		//brass card index is the place in the player's hand containing the selected card (1-8)
		//DO THIS
		//call a method in BrassGame to figure out if a card was clicked on (getSelectedCard)
		int brass_card_index = brass_game.getSelectedCard(x_click, y_click);

		//each BrassState class has a reference to the BrassGame
		//so that the state can inform the game when something meaningful has occurred
		if (brass_card_index > 0)
		{
			//DO THIS
			//when a valid card is selected, tell the game which card was selected (selectCard)

			brass_game.selectCard(brass_card_index);


			//tell the game to change the state to BrassSelectActionState (call getSelectActionState() to get the action state and then call changeState() to that action state)

			BrassState select_action_state = brass_game.getSelectActionState();

			brass_game.changeState(select_action_state);

			return;
		}

		//a valid card was not selected, so do nothing, stay in this state
	}
}
