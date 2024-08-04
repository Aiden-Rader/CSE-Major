import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Iterative 
//Iterative use do-while statements
{	
	public static void main(String [] args)
	{
		double start, end;
		double total;
		
		String path = "C:\\Users\\aiden\\Documents\\2500 EECS\\Recursion.txt";
		List<String> word = new ArrayList<>();
		
		String seg; 
		
		start = System.currentTimeMillis()/1000.0;
		
		try (BufferedReader reader = new BufferedReader(new FileReader(path)))
		{
			FileInputStream fileIn = new FileInputStream (path);
			Scanner userIn = new Scanner(fileIn);
			String str = userIn.nextLine();
			
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
		
		String [] strAr = word.toArray(new String[0]);
			
		for (String str : strAr) 
		{
			int left = 0; 
			int right = str.length() - 1;
			
			boolean pal = true;
			
			while (left < right && pal)
			{
				if (str.charAt(left) != str.charAt(right))
				{
					pal = false;
				}
				else
				{
					left++;
					right--;
				}
			}
			end = System.currentTimeMillis()/1000.0;
			total = (end-start);
			System.out.print(total);
		}
		
		
	}
}
