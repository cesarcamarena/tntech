package mastermind;

public class MasterMindAIState implements MasterMindState
{
	private MasterMind game;
	private MasterMindAI[] ai_list;
	private int current_ai;

	public MasterMindAIState(MasterMind game)
	{
		this.game = game;

		current_ai = 1;

		ai_list = new MasterMindAI[3];

		ai_list[0] = new MasterMindAIRandom(game);

		ai_list[1] = new MasterMindAIConsistent(game);

		ai_list[2] = new MasterMindAIMiniMax(game);
	}

	public void mouseClicked(int x_click, int y_click)
	{
		int change_ai = game.changeAI(x_click, y_click);

		if (game.isGameOver())
		{
			game.changeState(game.getGameOverState());
			return;
		}

		if (change_ai == 0)
		{
			game.changeState(game.getPlayerState());
			return;
		}

		else if (change_ai > 0)
		{
			current_ai = change_ai;
		}

		else
		{
			MasterMindAI ai = ai_list[current_ai - 1];

			game.addGuess(ai.nextGuess());
		}
	}

	public void setAI(int ai)
	{
		current_ai = ai;
	}
}