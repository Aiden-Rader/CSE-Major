/* Name: Aiden Rader
 * Class: EECS 2500
 * Professor: Dr.Thomas
 * Date: 9/26/22
 * Project: Lab1-CardStack
 */

import java.util.Scanner;

@SuppressWarnings("unchecked")
public class CardStack  
{
	public static void main(String[] args) //Main Method 
	{
		Scanner A = new Scanner(System.in);
		
		int n = A.nextInt(); //User enters column data
		int m = A.nextInt(); //User enters row data

		LinkedStack<Integer>[][] K = new LinkedStack[n][m]; //Our Row and Column Two-Dimensional Array using a linkedstack, which is a class made in this project
				
		A.nextLine(); //User input for the String or the Card layout		
		
		LLNode<Integer> sNode2 = new LLNode<Integer>(n); 
		LLNode<Integer> sNode1 = new LLNode<Integer>(m);
		sNode1.setLink(sNode2); //Link Nodes of linked list together

		
		for(int i = 0; i < n; i++) //Loop Structure for input n, this will loop until chosen amount of columns in the array
		{
			for(int j = 0; j < m; j++) //Loop Structure for input m, this will loop (before n) until the chosen amounts of rows in the array
			{	
				K[i][j] = new LinkedStack<Integer>(); 
			}
			
		A.nextLine(); //Repeat scenario
		}
		
		//THIS PORTION WAS THE PART I WAS STUCK ON!
		for (n = 0; n < K.length; n++)
		{
			
			for (m = 0; m < K.length; m++)
			{
				
			}
		}
		
		A.close(); //Scanner close	
		System.out.println("Test 1: ");
	}
		public int convertInt(String I) //Converts User input into a int
		{
			int result = "A23456789TJQK".indexOf(I.charAt(2)) + 1;
			result += "CSDH".indexOf(I.charAt(1)) * 13;
			if (I.charAt(0)=='D')
			{
				result *= -1;
			}
			result += "L".indexOf(0) - 1; //All below are if its flipping left, right, bottom, top
			result += "R".indexOf(0) + 1;
			result += "T".indexOf(0) + 1;
			result += "B".indexOf(0) - 1;
			return result;
		} 
		
		public String convertStr(int S) //Converts User input into a str
		{
			String result = "";
			
			if (S>0)
			{
				result += "U"; //Pos int if user inputs "U"
			}
			else
			{
				S *= -1;
				result += "D"; //Neg int if user inputs "D"
			}
			
			int divide = S / 13; //Find quotient for C-H
			
			switch (divide)
			{
			case 0: 
				result += "C";
				break;
				
			case 1: 
				result += "S";
				break;
				
			case 2: 
				result += "D";
				break;
				
			case 3: 
				result += "H";
				break;
			}
			
			int rem = S % 13; //Find remainder for A-K
			
			switch (rem)
			{
			case 1: 
				result += "A";
				break;
			
			case 2:
				result += "2";
				break;
				
			case 3:
				result += "3";
				break;
				
			case 4:
				result += "4";
				break;
				
			case 5:
				result += "5";
				break;
				
			case 6:
				result += "6";
				break;
				
			case 7:
				result += "7";
				break;
				
			case 8:
				result += "8";
				break;
				
			case 9:
				result += "9";
				break;
				
			case 10:
				result += "T";
				break;
				
			case 11:
				result += "J";
				break;
				
			case 12:
				result += "Q";
				break;
				
			case 13:
				result += "K";
				break;
			}
			return result; //Returns result 
			
		}
}
	

