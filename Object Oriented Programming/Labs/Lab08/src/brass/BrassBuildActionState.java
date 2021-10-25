package brass;

class BrassBuildActionState implements BrassState
{
	private BrassGame brass_game;

	private int brass_card_city_tech_id; //brass_card_id is the city/industry identifier for the card

	public BrassBuildActionState(BrassGame game)
	{
		brass_game = game;
		brass_card_city_tech_id = 0;
	}

	//DO THIS
	//need a setSelectedCard method to store the forwarded information (integer parameter) in brass_card_city_tech_id
	public void setSelectedCard(int id)
	{
		brass_card_city_tech_id = id;
	}


	//1 through 19 are city cards, 20 through 24 are industry cards
	//20 = coal, 21 = cotton, 22 = iron works, 23 = port, 24 = shipyard
	public void mouseClicked(int x_click, int y_click)
	{
		//first, check to see if the player wants to cancel the action
		int brass_action_id = brass_game.getSelectedAction(x_click, y_click);
		if (brass_action_id == BrassActionEnum.CANCEL.getValue())
		{
			brass_game.cancelCardSelection();
			brass_game.changeState(brass_game.getSelectCardState());
			return;
		}

		//if the card is a city card, the player clicks on a token location as the city is implied by the card
		//if the card is an industry card, the player clicks on a city as the industry is implied by the card

		int player_id = brass_game.getActivePlayerID();
		boolean can_build_industry = false;
		int city_id = -1;
		int industry_id = -1;
		if (brass_card_city_tech_id < 20)  //a city card
		{
			System.out.println("CITY ID IS" + brass_card_city_tech_id);
			//DO THIS
			//get the industry_id clicked on (getSelectedToken on brass_game)
			//get the city_id from brass_card_city_tech_id
			//if the industry_id > 0, test to see if the build can proceed through canBuildIndustry on brass_game, assigning the result to can_build_industry
			industry_id = brass_game.getSelectedToken(x_click, y_click);
			city_id = brass_card_city_tech_id;

			if (industry_id > 0)
			{
				can_build_industry = brass_game.canBuildIndustry(true, city_id, industry_id, player_id);
			}
		}

		else //the card is an industry card which is like a city card when the player has no tokens on the board
		{
			//DO THIS
			//get the city_id clicked on (use getSelectedCity on brass_game)
			//also, subtract 19 from brass_card_city_tech_id to get the industry_id
			//if the city_id > 0, test to see if the build can proceed, assigning the result to can_build_industry
			city_id = brass_game.getSelectedCity(x_click, y_click);

			industry_id = brass_card_city_tech_id - 19;

			if (city_id > 0)
			{
				can_build_industry = brass_game.canBuildIndustry(false, city_id, industry_id, player_id);
			}
		}

		//we adopt the convention of checking that the move is valid before performing any part of the action
		//we use asserts to detect when an invalid action is being attempted which probably
		//means the checking code has a bug
		if (can_build_industry)
		{
			brass_game.buildIndustry(city_id, industry_id, player_id);  //take the token from the player and place it on the board
			brass_game.playerActionCompleted();  //next player
		}
		else  //cancel action as required build conditions are not met
		{
			brass_game.cancelCardSelection();
		}

		brass_game.changeState(brass_game.getSelectCardState());
		brass_card_city_tech_id = 0;
	}
}
