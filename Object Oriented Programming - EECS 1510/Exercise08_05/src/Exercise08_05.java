/*S22 - EECS 1510
 * Problem 8-5, Revel Chapter 8 Project 2
 * Instructor: Dr.Hobbs
 * Written by: Hobbs
 * Date: 02-06-22
 * 
 * (Algebra: add two matrices)
 * Write a method to add two matrices. The header of the method is as follows
 * public static double[][] addMatrix(double[][] m1, double[][] m2)
 * 
 * See problem statement on BB or in the revel etext for the matrix layout
 * 
 * Write a test program that prompts the user to enter two 3x3 matrices and 
 * displays their sum.
 * 
 * 
 */

import java.util.*;

public class Exercise08_05
{

	public static void main(String[] args)
	{
		final int N = 3;
		final int M = 3;

		// need user to input matrix 1
		Scanner input = new Scanner(System.in); // need a Scanner
		System.out.print("Enter matrix1: ");
		double[][] matrix1 = new double[N][M];

		// I need nested for loops to put the user input into the proper
		// matrix1 locations
		for (int i = 0; i < matrix1.length; i++)
			for (int j = 0; j < matrix1[0].length; j++)
			{
				matrix1[i][j] = input.nextDouble();
			}

		// need user to input matrix 2
		// YOU DO MATRIX2
		System.out.print("Enter matrix2: ");
		double[][] matrix2 = new double[N][M];

		for (int i = 0; i < matrix2.length; i++)
			for (int j = 0; j < matrix2[0].length; j++)
			{
				matrix2[i][j] = input.nextDouble();
			}


		// need to add the two matrices by calling the addMatrix method
		double[][] resultMatrix = addMatrix(matrix1, matrix2);
		input.close();

		// going to use another method to print the result
		for (int i = 0; i < resultMatrix.length; i++)
		{
			for (int j = 0; j < resultMatrix[i].length; j++)
			{
				System.out.print(matrix1[i][j] + " ");
				if (i == 1 && j == 2)
				{
					System.out.print(" + ");
				} else
				{
					System.out.print("   ");
				}
			}
			for (int j = 0; j < resultMatrix[i].length; j++)
			{
				System.out.print(matrix2[i][j] + " ");
				if (i == 1 && j == 2)
				{
					System.out.print(" = ");
				} else
				{
					System.out.print("   ");
				}
			}
			for (int j = 0; j < resultMatrix[i].length; j++)
			{
				System.out.print(resultMatrix[i][j] + " ");
			}
			System.out.println();
		}
	}

	public static double[][] addMatrix(double[][] m1, double[][] m2)
	{
		double[][] result = new double[m1.length][m1[0].length];
		for (int i = 0; i < result.length; i++)
			for (int j = 0; j < result[i].length; j++)
				result[i][j] = m1[i][j] + m2[i][j];
		return result;
	}

}
