package mastermind;

public class MasterMindPlayerState implements MasterMindState
{
	private MasterMind game;

	public MasterMindPlayerState(MasterMind game)
	{
		this.game = game;
	}

	public void mouseClicked(int x_click, int y_click)
	{
		if (game.isGameOver())
		{
			game.changeState(game.getGameOverState());
			return;
		}

		if (game.isPlayerGuessComplete())
		{
			int state_id = game.changeAI(x_click, y_click);

			if (state_id > 0)
			{
				MasterMindState ai_state = game.getAIState();

				game.changeState(ai_state);

				((MasterMindAIState)ai_state).setAI(state_id);

				return;
			}
		}

		int color_selected = game.isColorSelected(x_click, y_click);

		if (color_selected > 0)
		{
			game.addGuess(color_selected);
		}
	}
}