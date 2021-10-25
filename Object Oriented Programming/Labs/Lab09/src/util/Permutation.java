package util;

public interface Permutation
{
   /**
   Preconditions: None.
   Postconditions: Returns a boolean whether the permuation has another random number.
   Throws: None.
   */
   public boolean hasNext();

   /**
   Preconditions: None.
   Postconditions: Returns the next random number in the permutation.
   Throws: None.
   */
   public int next();
}
