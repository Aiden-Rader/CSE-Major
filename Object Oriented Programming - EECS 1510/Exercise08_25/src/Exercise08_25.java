/* Spring 2022 EECS 1510
 * Instructor: Dr. Hobbs
 * Written By: Dr. Hobbs
 * This is Exercise 08-25 -- Revel Ch. 8 Prog. Project 4
 * 
 * 
 * (Markov matrix)
 * An n by n matrix is called a positive Markov matrix if 
 * each element is positive and the sum of the elements in 
 * each column is 1. Write the following method to check whether 
 * a matrix is a Markov matrix.
 * 
 * public static boolean isMarkovMatrix(double[][] m)
 * 
 * Write a test program that prompts the user to enter a 
 * 3 by 3 matrix of double values and tests whether it is a 
 * Markov matrix. 
 * Here are sample runs:
 * 
 * Sample Run 1
 * Enter a 3-by-3 matrix row by row:
 * 0.15 0.875 0.375
 * 0.55 0.005 0.225
 * 0.30 0.12 0.4
 * It is a Markov matrix
 * 
 * Sample Run 2
 * Enter a 3-by-3 matrix row by row:
 * 0.95 -0.875 0.375
 * 0.65 0.005 0.225
 * 0.30 0.22 -0.4
 * It is not a Markov matrix
 * 
 */


import java.util.*;
public class Exercise08_25
{

	public static void main(String[] args)
	{
		//need a scanner
		Scanner input = new Scanner(System.in);
		
		//matrix is 3 x 3 all the time, so set that up
		
		final int SIZE = 3;
		
		//ask the user to input a 3x3 matrix
		System.out.print("Enter a 3 by 3 matrix row by row: ");
		
		//create the place for the user input to be stored
		double [][] m = new double[SIZE][SIZE];
		
		//need to store the user input into my matrix m
		
		for(int i = 0; i < m.length; i++)
			for(int j = 0; j < m[0].length; j++)
				m[i][j] = input.nextDouble();
		
		
		//we need to print one of two messages to the console
		//the matrix either is a Markov or it is not a Markov
		//we need a conditional statement...we can make the method
		//call from inside the conditional statement.
		
		if(isMarkovMatrix(m))
			System.out.print("It is a Markov matrix");
		else
			System.out.print("It is not a Markov matrix");
	input.close();
	}
	
	public static boolean isMarkovMatrix(double[][] m)
	{
		//make sure every element is positive
		for(int i = 0; i < m.length; i++)
			for(int j = 0; j < m[0].length; j++)
				if(m[i][j] < 0) return false;
			
		//if all positive, check the sum of each column
		//if sum is 1, then Markov; otherwise not Markov
		for(int j = 0; j < m[0].length; j++)
		{
			double sum = 0.0;
			for(int i = 0; i < m.length; i++)
				sum += m[i][j];
			if (sum != 1)
				return false;
		}
		return true;
		
		
	}

}
