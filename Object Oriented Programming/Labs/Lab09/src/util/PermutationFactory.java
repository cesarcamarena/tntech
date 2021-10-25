package util;

public class PermutationFactory
{
   /**
   Preconditions:  Requires a file name, how many random numbers you want, and your
				   highest limit for the random numbers.
   Postconditions: Returns a permutation from 1 to n, and has r amount of random numbers.
   Throws: None.
   */
   public static Permutation getPermutation(String file_name, int r, int n)
   {
	   return new FilePermutation(file_name, r);
	   //return new RandomPermutation(r, n);
   }
}
