package mastermind;

public class MasterMindAIConsistent implements MasterMindAI
{
	private MasterMind game;

	boolean good_guess = false;

	public MasterMindAIConsistent(MasterMind game)
	{
		this.game = game;
	}

	public Guess nextGuess()
	{
		Guess random_guess = new Guess(game.getNumGuesses() + 1);

		util.Random random = util.Random.getRandomNumberGenerator();

		for (int i = 1; i <= 4; i++)
		{
			int random_int = random.randomInt(1, 7);
			random_guess.addColor(random_int);
		}

		if (game.getNumGuesses() == 0)
		{
			return random_guess;
		}

		Guess consistent_guess;

		do
		{			consistent_guess = new Guess(game.getNumGuesses() + 1);

			for (int i = 1; i <= 4; i++)
			{
				int random_int = random.randomInt(1, 7);
				consistent_guess.addColor(random_int);
			}

			for (int i = 1; i <= game.getNumGuesses(); i++)
			{
				Guess previous_guess = game.getGuess(i);

				Guess comparison_guess = new Guess(previous_guess);

				previous_guess.computeResult(consistent_guess);

				if (comparison_guess.getNumBlack() == previous_guess.getNumBlack() && comparison_guess.getNumWhite() == previous_guess.getNumWhite())
				{
					good_guess = true;
				}

				else
				{
					good_guess = false;
					break;
				}
			}
			
		} while (!good_guess);

		return consistent_guess;
	}

}