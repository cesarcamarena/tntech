package mastermind;

import java.util.List;
import java.util.ArrayList;

public class MasterMindAIMiniMax implements MasterMindAI
{
	private MasterMind game;
	private ArrayList<Guess> all_guesses;
	private ArrayList<Guess> possible_guesses;

	public MasterMindAIMiniMax(MasterMind game)
	{
		this.game = game;

		all_guesses = new ArrayList<Guess>();

		for (int i = 1; i <= 7; i++)
		{
			for (int j = 1; j <= 7; j++)
			{
				for (int k = 1; k <= 7; k++)
				{
					for (int l = 1; l <= 7; l++)
					{
						Guess guess = new Guess(game.getNumGuesses() + 1);

						guess.addColor(i);
						guess.addColor(j);
						guess.addColor(k);
						guess.addColor(l);

						all_guesses.add(guess);
					}
				}
			}
		}

		possible_guesses = new ArrayList<Guess>(all_guesses);
	}

	public Guess nextGuess()
	{
		if (game.getNumGuesses() == 0)
		{
			Guess guess = new Guess(1);

			for(int i = 1; i <= 4; i++)
			{
				guess.addColor(i);
			}

			return guess;
		}


		for (int i = 1; i <= game.getNumGuesses(); i++)
		{
			Guess previous_guess = game.getGuess(i);

			for (int j = 0; j < possible_guesses.size(); j++)
			{
				Guess current_guess = possible_guesses.get(j);

				int[] buttons = game.reportTestResult(current_guess, previous_guess);

				if (buttons[0] != previous_guess.getNumBlack() || buttons[1] != previous_guess.getNumWhite())
				{
					possible_guesses.remove(j);
					j--;
				}
			}
		}

		Guess best_guess = null;
		//int max = 0;

		for (Guess guess_from_possible_guesses : possible_guesses)
		{
			int min = 0;

			for (int blacks = 0; blacks <= 4; blacks++)
			{
				for (int whites = 0; whites <= (4 - blacks); whites++)
				{
					int count = 0;

					for (Guess guess_from_all_guesses : all_guesses)
					{
						int[] blacks_and_whites = guess_from_possible_guesses.reportResult(guess_from_all_guesses);

						if (blacks_and_whites[0] != blacks || blacks_and_whites[1] != whites)
						{
							count++;
						}
					}

					if (min <= count)
					{
						min = count;

						best_guess = new Guess(game.getNumGuesses() + 1);

						List<Integer> color_ids = guess_from_possible_guesses.getGuessColorIDs();

						for (int i = 0; i < color_ids.size(); i++)
						{
							int color = color_ids.get(i);

							best_guess.addColor(color);
						}
					}
				}
			}

		}

		return best_guess;
	}
}