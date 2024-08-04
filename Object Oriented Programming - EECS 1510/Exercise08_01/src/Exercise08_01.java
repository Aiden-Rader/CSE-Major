/* EECS 1510
 * Problem 8-1, Revel Chapter 8 Project 1
 * Instructor: Dr.Hobbs
 * Written by: Hobbs
 * Date: 02-05-22
 * 
 * (Sum elements column by column)
 * Write a method that returns the sum of all the elements in a specified 
 * column in a matrix using the following header:
 * public static double sumColumn(double[][] m, int columnIndex)
 * Write a test program that reads a 3-by-4 matrix and displays the sum 
 * of each column.
 * 
 * Sample Run
 * Enter a 3-by-4 matrix row by row:
 * 1.5 2 3 4
 * 5.5 6 7 8
 * 9.5 1 3 1
 * 
 * Sum of the elements at column 0 is 16.5
 * Sum of the elements at column 1 is 9.0
 * Sum of the elements at column 2 is 13.0
 * Sum of the elements at column 3 is 13.0
 * 
 */

import java.util.*;
public class Exercise08_01
{	
	
	public static void main(String[] args)
	{   //need a scanner
		Scanner input = new Scanner(System.in);
		
		//prompt the user to enter a 3x4 matrix row by row
		System.out.print("Enter a 3 by 4 matrix row by row: ");
		//need a place to sort the matrix
		double [][] m = new double [3][4];
		
		//need to place the input in the proper row and column of the matrix
		//probably need nested for loops.
		
		for(int i=0; i < m.length; i++)
			for(int j=0; j < m[i].length; j++)
				m[i][j] = input.nextDouble();
		
		//sum the elements of each column.
		//need loop
		//I am going to start the print statement here and then call the sum
		//method.
		for(int j=0; j < m[0].length; j++)
		{
			System.out.println("Sum of the elements at column " + j + " is " +
									sumColumn(m,j));
		}
		
		

	}
	
	public static double sumColumn(double[][] m, int columnIndex)
	{
	double total = 0;
	
	for(int i = 0; i < m.length; i++)
		total += m[i][columnIndex];
	return total;
	}

}
