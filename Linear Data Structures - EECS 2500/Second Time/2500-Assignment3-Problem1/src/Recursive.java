import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Recursive 
//The Recursive program should follow an if-else statement

//Our goal is to determine if a string is a palindrome using a recursive solution
{
	public static boolean isPal(String ste)
	{
		return isPal(ste, 0, ste.length() - 1); //string (user inputed), location of first letter, location of last letter
	}
	
	private static boolean isPal(String ste, int first, int last)
	{
		if (last <= first) 
			return true;
		
		else if (ste.charAt(first) != ste.charAt(last)) //if first and last letter are not the same
			return false; 
		
		else //loops by calling itself over and over again as the first and last letters are getting closer together
			return isPal(ste, first + 1, last - 1);
	}

	public static void main(String [] args)
	{
		double start, end;
		double total;
		
		String path = "C:\\Users\\aiden\\Documents\\2500 EECS\\Recursion.txt";
		List<String> word = new ArrayList<>();
		
		String seg;
		
		try (BufferedReader reader = new BufferedReader(new FileReader(path)))
		{
			FileInputStream fileIn = new FileInputStream (path);
			Scanner userIn = new Scanner(fileIn);
		
			   while ((seg = reader.readLine()) != null) 
			   {
	                String[] tokens = seg.split("[.,]");
	                for (String token : tokens) 
	                {
	                    word.add(token.trim());
	                }
	            }
	    } 
		
		catch (IOException e) 
		{
	            e.printStackTrace();
	    }

			
			//Recursion starts here
			start = System.currentTimeMillis()/1000.0;
			
		
			String [] strAr = word.toArray(new String[0]);
			
			for (String s : strAr)
				isPal(s);
			
			end = System.currentTimeMillis()/1000.0;
			total = (end-start);
			System.out.print(total);
		
		} 
}

