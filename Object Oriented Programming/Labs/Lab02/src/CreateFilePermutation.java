import util.Keyboard;
import util.RandomPermutation;
import util.PermutationFactory;
import util.Random;
import util.WriteTextFile;
import util.ReadTextFile;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class CreateFilePermutation
{
	
	public static void main(String[] args)
	{
		//DO THIS
		//use the Keyboard class to obtain the upper integer value

		Keyboard kb = Keyboard.getKeyboard();
		
		int n = kb.readInt("Enter an integer: ");
		
		String fileName = kb.readString("Enter the name of the output file for the permutation: ");
		
		
		
		
		
		//DO THIS
		//obtain the random permutation using the upper integer value
		//write out the values to a text file (close the file)
		
		RandomPermutation rp = new RandomPermutation(n, n);
		
		WriteTextFile wf = new WriteTextFile(fileName);
		
		int nextNum;
		
		while (rp.hasNext())
		{
			nextNum = rp.next();
			
			wf.writeLine(nextNum + "");
		}
		wf.close();

		
		
		
		
		//DO THIS
		//read the values in from the text file and store them in an integer array
		//it is easiest to read the first line outside of a while loop that tests for EOF
		
		ArrayList<Integer> arrayList = new ArrayList<Integer>(n);
		
		ReadTextFile rtf = new ReadTextFile("resources/brass_deck_shuffle.txt");
		
		String randNum = rtf.readLine();
		
		while(!rtf.EOF())
		{
			arrayList.add(Integer.parseInt(randNum));
			randNum = rtf.readLine();
		}
		rtf.close();
		
		
		
		
		
		
		//DO THIS
		//sort the integers (use java.util.Arrays.sort)
		//print them out to make sure they are all there once

		Collections.sort(arrayList);
		
		System.out.println(arrayList);
		
		
		
		
	}
}