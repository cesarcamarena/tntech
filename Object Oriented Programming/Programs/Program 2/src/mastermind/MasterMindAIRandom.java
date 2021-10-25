package mastermind;

public class MasterMindAIRandom implements MasterMindAI
{
	private MasterMind game;

	public MasterMindAIRandom(MasterMind game)
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

		return random_guess;
	}
}