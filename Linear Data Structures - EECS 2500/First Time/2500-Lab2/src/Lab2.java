import java.io.File;
import java.io.IOException;
import java.util.Scanner;

/* Name: Aiden Rader
 * EECS 2500
 * Lab #2
 * Dr.Lawrence Thomas 
*/
public class Lab2 
{
//IN this lab we will call and output are results
	
//WE also use the Fileinput line in the main
	
	public static void main(String[] args) throws IOException
	{
		
		ListInterface[] Lists = new ListInterface[4]; // By creating the lists as an array, we can iterate with a subscript
		
		Lists[0] = new List1(); // Unsorted linked list		
		Lists[1] = new List2(); // Sorted linked list
		Lists[2] = new List3(); // Unsorted, heavy-handed self-adjusting (moves repeated word to the front of the list)
		Lists[3] = new List4(); // Unsorted, conservative self-adjusting (moves repeated word one position towards front of list)
		
		String[] ListNames = {"Unsorted", "Sorted", "Self-Adj (Front)", "Self-Adj (By One)"};
		
		for (int i=0; i < Lists.equals(ListNames[0]; i++);
		{
			
		}
		
		//Figure out filereader for individual lists
		
		File file = new File("Hamlet.txt");
		Scanner info = new Scanner(file);
		StringBuilder inFile = new StringBuilder();
		
		int a;
		while ((a = fileRead.read()) != -1)
		{
			inFile.append(a);
		}
		
	
		
		
		//Use a stringbuilder to remove punctuation
		
		
		
		
		
		//Output to console code 
	}
	
	
	
	
	
	
	
	
	

} // End of Main